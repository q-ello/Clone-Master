#include "Game.h"
#include "Utilities/Utils.h"

void Game::play()
{
	initWorld();

	run();

	dispose();
}

void Game::initWorld()
{
	std::ifstream f("data/data.json");
	json data = json::parse(f);
	parseData(data);
}

void Game::run()
{
	isRunning_ = true;

	printIntroduction();

	currentRoom_->printRoomInfo();

	while (isRunning_)
	{
		std::cout << "\n>";
		Instruction inst = Input::ReadUser();
		std::cout << std::endl;
		updateState(inst);
	}
}

void Game::dispose()
{
	rooms_.clear();
	inventory_.dispose();
}

void Game::printIntroduction()
{
	std::cout << "They said your experiments were illegal and named you a madman. "
		<< "They locked you up on an underground military base, took away your precious inventions. "
		<< "Feeble minds!They shall never understand… You will show them! " << std::endl
		<< "But first you need to get out of here and get your equipment back…" << std::endl << std::endl;
}

void Game::updateState(Instruction instruction)
{
	switch (instruction.function)
	{
	case F_GO:
		go(instruction.goal);
		break;
	case F_SAVE:
		save();
		break;
	case F_RESTORE:
		restore();
		break;
	case F_LOOK:
		currentRoom_->printRoomInfo();
		break;
	case F_HELP:
		help();
		break;
	case F_TAKE:
		take(instruction.goal);
		break;
	case F_INVENTORY:
		printInventory();
		break;
	case F_DROP:
		drop(instruction.goal);
		break;
	case F_QUIT:
		quit();
		break;
	default:
		std::cout << "Excuse you?\n";
		break;
	}
}

void Game::go(const std::string& direction)
{
	Direction dir;
	if (!DirectionsToEnum.contains(direction))
	{
		std::cout << "You can't go that way.\n";
		return;
	}
	dir = DirectionsToEnum[direction];

	std::string id;
	if (currentRoom_->getExitId(dir, id))
	{
		currentRoom_ = rooms_[id];
		currentRoom_->printRoomInfo();
	}
}

void Game::save()
{
	std::ofstream f("data/savefile.json");
	json j;
	j["current"] = currentRoom_->getName();
	json roomsJson;
	for (const auto& [key, room] : rooms_)
	{
		json roomJson;
		roomJson["name"] = room->getName();
		roomJson["description"] = room->getDescription();

		json exitsJson;
		for (const auto& [direction, exit] : room->getExits())
		{
			json exitJson;
			exitJson["direction"] = DirectionsToString.at(direction);
			exitJson["name"] = exit.name;
			if (!exit.available)
			{
				exitJson["available"] = false;
			}
			exitsJson.push_back(exitJson);
		}
		roomJson.emplace("exits", exitsJson);

		json itemsJson;

		for (const auto& item : room->getItems())
		{
			json itemJson;
			itemJson["name"] = item->getName();
			itemJson["description"] = item->getDescription();
			itemJson["clue"] = item->getClue();
			if (!item->isAvailable())
			{
				itemJson["available"] = false;
			}
			itemsJson.push_back(itemJson);
		}
		roomJson.emplace("items", itemsJson);

		roomsJson.push_back(roomJson);

	}

	j.emplace("rooms", roomsJson);


	json inventoryJson;

	for (const auto& item : inventory_.getEntities())
	{
		json itemJson;
		itemJson["name"] = item->getName();
		itemJson["description"] = item->getDescription();
		itemJson["clue"] = item->getClue();
		inventoryJson.push_back(itemJson);
	}

	j.emplace("inventory", inventoryJson);

	f << std::setw(4) << j << std::endl;

	std::cout << "Your progress was saved." << std::endl;
}

void Game::restore()
{
	std::ifstream f;
	f.open("data/savefile.json");
	if (!f)
	{
		std::cout << "You don't have any progress saved.\n";
		return;
	}
	json data = json::parse(f);
	parseData(data);
	std::cout << "Your progress was restored. Enjoy your game!\n\n";
	currentRoom_->printRoomInfo();
}

void Game::parseData(json data)
{
	for (auto& roomJson : data.at("rooms"))
	{
		std::string name = roomJson.at("name");
		auto descIt = roomJson.find("description");
		std::string description = "";
		if (descIt != roomJson.end())
		{
			description = *descIt;
		}
		Room* newRoom = new Room(name, description);
		for (auto& exitJson : roomJson.at("exits"))
		{
			newRoom->addExit(DirectionsToEnum.at(exitJson.at("direction")), 
				exitJson.at("name"), 
				exitJson.find("available") == exitJson.end());
		}
		if (roomJson.contains("items"))
		{
			for (auto& itemJson : roomJson.at("items"))
			{
				std::string name = itemJson.at("name");
				std::string description = itemJson.at("description");
				std::string clue = itemJson.at("clue");
				bool available = itemJson.find("available") == itemJson.end();
				newRoom->addItem(new Item(name, description, clue, available));
			}
		}

		rooms_[name] = newRoom;
	}

	currentRoom_ = rooms_.at(data.at("current"));

	auto inventoryIt = data.find("inventory");

	if (inventoryIt != data.end())
	{
		for (auto& itemJson : *inventoryIt)
		{
			std::string name = itemJson.at("name");
			std::string description = itemJson.at("description");
			std::string clue = itemJson.at("clue");
			inventory_.addEntity(new Item(name, description, clue, true));
		}
	}
}

void Game::help()
{
	std::cout << "- help/? - see help" << std::endl;
	std::cout << "- go north/go n/north/n - go north, and etc for east/south/west/up/down" << std::endl;
	std::cout << "- good news, you can save your progress! to do that type 'save'" << std::endl;
	std::cout << "- restore - restore your progress" << std::endl;
	std::cout << "- l/look - look around the room you currently in" << std::endl;
	std::cout << "- i/inventory - look in your inventory" << std::endl;
	//std::cout << "- talk to smb - enter the dialogue with some npc" << std::endl;
	std::cout << "- take/pick up smth - put something in your inventory" << std::endl;
	std::cout << "- drop smth - drop something from your inventory back into the room" << std::endl;
	//TODO quit
	//TODO examine
	//TODO clone
	//TODO leave
	//TODO equip
	//TODO unequip
	std::cout << "P.S. so, I know you're all lazy like me and don't wanna type long names. so don't. one word is enough, really" << std::endl;
}

void Game::take(std::string item)
{
	if (inventory_.isFull())
	{
		std::cout << "You already have too much items in your inventory.\n";
		return;
	}

	Item* neededItem = currentRoom_->getItemByName(item);

	if (neededItem == nullptr)
	{
		std::cout << "You cannot take " << item << std::endl;
		return;
	}

	inventory_.addEntity(std::move(neededItem));
	std::cout << "Taken.\n";
}

void Game::drop(std::string item)
{
	Item* droppedItem = inventory_.deleteEntity(item);

	if (droppedItem == nullptr)
	{
		std::cout << "You do not even have " << item << " in your inventory" << std::endl;
		return;
	}

	currentRoom_->addItem(std::move(droppedItem));

	std::cout << "Dropped.\n";
}

void Game::printInventory()
{
	if (inventory_.isEmpty())
	{
		std::cout << "You have nothing.\n";
		return;
	}

	std::cout << "Here are the items you possess:" << std::endl;
	inventory_.printInfo();
}

void Game::quit()
{
	std::vector<std::string> options = { "Save", "Quit", "Continue playing"};
	int choice = Utils::menu(options);

	switch (choice)
	{
	case 0:
		save();
		break;
	case 2:
		return;
	default:
		break;
	}

	isRunning_ = false;
}

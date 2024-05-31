#include "Game.h"
#include "Utilities/Utils.h"
#include "Models/Trigger.h"
#include "Models/NPC.h"

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
	std::cout << "Thanks for playing!" << std::endl;

	rooms_.clear();
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
	if (isInCombat_ && instruction.function != F_ATTACK && instruction.function != F_GIVE)
	{
		std::cout << "You cannot do that, you are in combat now." << std::endl;
		getAttacked();
		return;
	}

	switch (instruction.function)
	{
	case F_GO:
		if (instruction.goal == "")
		{
			std::cout << "Where do you wanna go?\n";
			int choice = Utils::menu({ "north", "east", "south", "west", "up", "down", "nowhere" });
			switch (choice)
			{
			case 0:
				instruction.goal = "n";
				break;
			case 1:
				instruction.goal = "e";
				break;
			case 2:
				instruction.goal = "s";
				break;
			case 3:
				instruction.goal = "w";
				break;
			case 4:
				instruction.goal = "u";
				break;
			case 5:
				instruction.goal = "d";
				break;
			default:
				return;
			}
		}
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
		if (inventory_.isEmpty())
		{
			std::cout << "You don't have anything to drop" << std::endl;
			return;
		}

		if (instruction.goal == "")
		{
			std::cout << "What do you want to drop?" << std::endl;
			std::vector names = inventory_.getEntitiesNames();
			names.push_back("Nothing");
			int choice = Utils::menu(names);
			if (choice == names.size() - 1)
				return;
			drop(choice);
			return;
		}

		drop(instruction.goal);
		break;
	case F_QUIT:
		quit();
		break;
	case F_EXAMINE:
		examine(instruction.goal);
		break;
	case F_MOVE:
		move(instruction.goal);
		break;
	case F_ATTACK:
		if (instruction.goal == "" && currentEnemy_ != nullptr)
		{
			attack();
			return;
		}
		attack(instruction.goal);
		break;

	case F_GIVE:
		if (instruction.goal == "")
		{
			std::cout << "What do you want to give?" << std::endl;
			std::vector<std::string> names = inventory_.getEntitiesNames();
			names.push_back("Nothing");
			int choice = Utils::menu(names);
			if (choice == names.size() - 1)
				return;
			std::cout << "Whom do you want to give it to?" << std::endl;
			std::getline(std::cin, instruction.object);
			give(choice, instruction.object);
			return;
		}
		give(instruction.goal, instruction.object);
		break;
	case F_CLONE:
		if (!canClone_)
		{
			std::cout << "You are a clone master, but you do not make clones with your willpower only." << std::endl;
			return;
		}
		if (charges_ == 0)
		{
			std::cout << "You don't have charges to do that." << std::endl;
			return;
		}
		if (instruction.goal == "me" || instruction.goal == "myself")
		{
			std::cout << "You really want to waste a battery to have a clone as weak as yourself?" << std::endl;
			return;
		}
		clone(instruction.goal);
		break;
	case F_RECRUIT:
		recruit(instruction.goal);
		break;
	case F_LEAVE:
		if (instruction.goal == "")
		{
			std::cout << "Who do you want to leave?" << std::endl;
			std::vector<std::string> names = squad_.getEntitiesNames();
			names.push_back("No one");
			int choice = Utils::menu(names);
			if (choice == names.size() - 1)
				return;
			leave(choice);
			return;
		}
		leave(instruction.goal);
		break;
	case F_OPEN:
		if (instruction.object == "")
		{
			std::cout << "What do you want to use to open it?" << std::endl;
			std::vector<std::string> names = inventory_.getEntitiesNames();
			names.push_back("Nothing");
			int choice = Utils::menu(names);
			if (choice == names.size() - 1)
				return;
			open(instruction.goal, choice);
			return;
		}
		open(instruction.goal, instruction.object);
		break;
	case F_USE:
		if (instruction.object == "")
		{
			std::cout << "What do you want to use?" << std::endl;
			std::vector<std::string> names = inventory_.getEntitiesNames();
			names.push_back("Nothing");
			int choice = Utils::menu(names);
			if (choice == names.size() - 1)
				return;
			std::cout << "What do you want to use it on?" << std::endl;
			std::getline(std::cin, instruction.goal);
			use(choice, instruction.goal);
			return;
		}
		use(instruction.object, instruction.goal);
		break;
	case F_SQUAD:
		squad();
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
	if (!currentRoom_->getExitId(dir, id))
	{
		return;
	}

	currentRoom_ = rooms_[id];
	currentRoom_->printRoomInfo();

	NPC* possibleEnemy = currentRoom_->isDangerous();

	if (possibleEnemy != nullptr)
	{
		isInCombat_ = true;
		currentEnemy_ = possibleEnemy;
	}
}

void Game::save()
{
	std::ofstream f("data/savefile.json");
	json j;
	j["current"] = currentRoom_->getName();
	json roomsJson;
	json npcsJson;
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

		json triggersJson;

		for (const auto& trigger : room->getTriggers())
		{
			json triggerJson;
			triggerJson["name"] = trigger->getName();
			triggerJson["clue"] = trigger->getClue();
			if (trigger->getAction() != T_NONE)
			{
				json triggerInfo;
				TriggerAction action = trigger->getAction();

				triggerInfo["type"] = TriggerTypesToString.at(trigger->getType());
				triggerInfo["action"] = TriggerActionsToString.at(trigger->getAction());
				triggerInfo["name"] = trigger->getEntityName();
				if (trigger->getKey() != "")
				{
					triggerInfo["key"] = trigger->getKey();
				}

				triggerJson.emplace("trigger", triggerInfo);
			}
			triggersJson.push_back(triggerJson);
		}

		roomJson.emplace("triggers", triggersJson);

		roomsJson.push_back(roomJson);

		for (auto& npc : room->getNPCs())
		{
			json npcInRoom;

			bool exists = false;

			for (auto& j : npcsJson)
			{
				if (j.at("name") == npc->getName())
				{
					j.at("rooms").push_back(room->getName());
					exists = true;
				}
			}

			if (exists)
				continue;

			npcInRoom["name"] = npc->getName();
			npcInRoom["hp"] = npc->getHP();
			npcInRoom["dmg"] = npc->damage();
			npcInRoom["hit_chance"] = npc->getHitChance();
			npcInRoom["can_clone"] = npc->canBeCloned();
			npcInRoom["is_recruitable"] = npc->isRecrutable();
			npcInRoom["in_room_alive"] = npc->getDescriptionAwake();
			npcInRoom["in_room_dead"] = npc->getDescriptionUnconscious();
			npcInRoom["greeting"] = npc->getGreeting();
			npcInRoom["incorrect_item_response"] = npc->incorrectItemResponse();
			npcInRoom["required_item"] = npc->requiredItem();
			npcInRoom["has_item_response"] = npc->hasItemResponse();
			npcInRoom["rooms"].push_back(room->getName());

			npcsJson.push_back(npcInRoom);
		}
	}

	j.emplace("rooms", roomsJson);
	j.emplace("npcs", npcsJson);

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

	json squadJson;

	for (const auto& npc : squad_.getEntities())
	{
		json npcJson;
		npcJson["name"] = npc->getName();
		npcJson["hp"] = npc->getHP();
		npcJson["dmg"] = npc->damage();
		npcJson["hit_chance"] = npc->getHitChance();
		npcJson["can_clone"] = npc->canBeCloned();
		npcJson["is_recruitable"] = npc->isRecrutable();
		npcJson["in_room_alive"] = npc->getDescriptionAwake();
		npcJson["in_room_dead"] = npc->getDescriptionUnconscious();
		npcJson["greeting"] = npc->getGreeting();
		npcJson["incorrect_item_response"] = npc->incorrectItemResponse();
		npcJson["required_item"] = npc->requiredItem();
		npcJson["has_item_response"] = npc->hasItemResponse();

		squadJson.push_back(npcJson);
	}

	j.emplace("squad", squadJson);

	j.emplace("dmg", dmg_);

	j.emplace("can_clone", canClone_);
	j.emplace("charges", charges_);

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

void Game::parseData(const json& data)
{
	for (auto& roomJson : data.at("rooms"))
	{
		std::string roomName = roomJson.at("name");
		auto descIt = roomJson.find("description");
		std::string roomDesc = "";
		if (descIt != roomJson.end())
		{
			roomDesc = *descIt;
		}
		Room* newRoom = new Room(roomName, roomDesc);

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
				std::string itemName = itemJson.at("name");
				std::string itemDesc = itemJson.at("description");
				std::string itemClue = itemJson.at("clue");
				bool itemAvailable = itemJson.find("available") == itemJson.end();
				newRoom->addItem(new Item(itemName, itemDesc, itemClue, itemAvailable));
			}
		}
		if (roomJson.contains("triggers"))
		{
			for (auto& triggerJson : roomJson.at("triggers"))
			{
				std::string triggerName = triggerJson.at("name");
				std::string triggerClue = triggerJson.at("clue");
				if (triggerJson.contains("trigger"))
				{
					json triggerInfo = triggerJson.at("trigger");
					TriggerAction action = TriggerActionsToEnum.at(triggerInfo.at("action"));
					std::string key = "";
					auto keyIt = triggerInfo.find("key");
					if (keyIt != triggerInfo.end())
						key = *keyIt;
					std::string entityName = triggerInfo.at("name");

					TriggerType type = TriggerTypesToEnum.at(triggerInfo.at("type"));

					Trigger* trig = new Trigger(triggerName, triggerClue, entityName, action, key, type);

					newRoom->addTrigger(std::move(trig));
					
				}
				else {
					newRoom->addTrigger(new Trigger(triggerName, triggerClue));
				}
			}
		}

		rooms_[roomName] = newRoom;
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
			inventory_.addEntity(new Item(name, description, clue));
		}
	}

	for (auto& npcJson : data.at("npcs"))
	{
		
		std::string name = npcJson.at("name");
		int HP = npcJson.at("hp");
		int dmg = npcJson.at("dmg");
		int hitChance = npcJson.at("hit_chance");
		bool canBeCloned = npcJson.at("can_clone");
		bool isRecrutable = npcJson.at("is_recruitable");
		std::string inRoomAwake = npcJson.at("in_room_alive");
		std::string inRoomUnconscious = npcJson.at("in_room_dead");
		std::string greeting = npcJson.at("greeting");
		std::string incorrectItemResponse = npcJson.at("incorrect_item_response");
		std::string requiredItem = "";
		std::string hasItemResponse = "";

		auto reqItemIt = npcJson.find("required_item");
		if (reqItemIt != npcJson.end())
		{
			requiredItem = *reqItemIt;
			hasItemResponse = npcJson.at("has_item_response");
		}

		NPC* newNPC = new NPC(name, dmg, hitChance, inRoomAwake, inRoomUnconscious, incorrectItemResponse, requiredItem, hasItemResponse,
			HP, greeting, canBeCloned, isRecrutable);

		for (auto& room : npcJson.at("rooms"))
		{
			rooms_[room]->addNPC(std::move(newNPC));
		}
	}

	auto squadIt = data.find("squad");

	if (squadIt != data.end())
	{ 
		for (json npcJson : *squadIt)
		{
			std::string name = npcJson.at("name");
			int HP = npcJson.at("hp");
			int dmg = npcJson.at("dmg");
			int hitChance = npcJson.at("hit_chance");
			bool canBeCloned = npcJson.at("can_clone");
			bool isRecrutable = npcJson.at("is_recruitable");
			std::string inRoomAwake = npcJson.at("in_room_alive");
			std::string inRoomUnconscious = npcJson.at("in_room_dead");
			std::string greeting = npcJson.at("greeting");
			std::string incorrectItemResponse = npcJson.at("incorrect_item_response");
			std::string requiredItem = npcJson.at("required_item");
			std::string hasItemResponse = npcJson.at("has_item_response");

			squad_.addEntity(new NPC(name, dmg, hitChance, inRoomAwake, inRoomUnconscious, incorrectItemResponse, requiredItem, hasItemResponse,
				HP, greeting, canBeCloned, isRecrutable));
		}
	}

	if (data.contains("dmg"))
	{
		dmg_ = data.at("dmg");
	}

	if (data.contains("can_clone"))
	{
		canClone_ = data.at("can_clone");
	}

	if (data.contains("charges"))
	{
		charges_ = data.at("charges");
	}
}

void Game::help()
{
	std::cout << "- help/? - see help" << std::endl;
	std::cout << "- (go north)/(go n)/north/n - go north, and etc for east/south/west/up/down" << std::endl;
	std::cout << "- good news, you can save your progress! to do that type 'save'" << std::endl;
	std::cout << "- restore - restore your progress" << std::endl;
	std::cout << "- l/look - look around the room you currently in" << std::endl;
	std::cout << "- i/inventory - look in your inventory" << std::endl;
	std::cout << "- take/pick up smth - put something in your inventory" << std::endl;
	std::cout << "- drop smth - drop something from your inventory back into the room" << std::endl;
	std::cout << "- examine smth - maybe you could find out some clues ;)" << std::endl;
	std::cout << "- use smth on smth/some other commands - sometimes you just need to give it a try" << std::endl;
	std::cout << "- squad - look who is in your squad" << std::endl;
	std::cout << "- clone sb - you're a clone master after all" << std::endl;
	std::cout << "- talk to smb - enter the dialogue with some npc" << std::endl;
	std::cout << "- give smth to sb - sometimes you can just negotiate" << std::endl;
	std::cout << "- attack sb - you don't need to worry about the weapon" << std::endl;
	std::cout << "- quit - quit game" << std::endl;
	std::cout << "P.S. so, I know you're all lazy like me and don't wanna type long names. so don't. one word is enough, really" << std::endl;
	std::cout << "P.P.S. sometimes you can even type only a command and get the list of options to choose" << std::endl;
}

void Game::take(const std::string& item)
{
	int i = currentRoom_->getItem(item);

	if (i == -1)
	{
		std::cout << "You cannot take " << item << "." << std::endl;
		return;
	}

	Item* neededItem = currentRoom_->getItem(i);

	if (item == "device")
	{
		canClone_ = true;
		std::cout << "Now you are in your whole power!" << std::endl;
		currentRoom_->deleteItem(i);

		return;
	}


	if (item == "charge")
	{
		charges_++;
		currentRoom_->deleteItem(i);
		std::cout << "Taken." << std::endl;
		return;
	}

	if (inventory_.isFull())
	{
		std::cout << "You already have too much items in your inventory.\n";
		return;
	}


	if (!neededItem->isAvailable())
	{
		std::cout << "You cannot take " << item << "." << std::endl;
		return;
	}

	currentRoom_->deleteItem(i);

	if (neededItem->getName() == "Battery")
	{
		
		delete neededItem;
	}
	else
	{
		inventory_.addEntity(std::move(neededItem));
	}

	std::cout << "Taken.\n";
}

void Game::drop(const std::string& name)
{
	int i = inventory_.getEntity(name);

	if (i == -1)
	{
		std::cout << "You do not even have " << name << " in your inventory." << std::endl;
		return;
	}

	drop(i);
}

void Game::drop(int i)
{
	Item* droppedItem = inventory_.getEntity(i);
	inventory_.deleteEntity(i);

	currentRoom_->addItem(std::move(droppedItem));

	std::cout << "Dropped.\n";
}

void Game::printInventory()
{
	if (inventory_.isEmpty())
	{
		std::cout << "You have nothing in your inventory.\n";
	}
	else
	{
		std::cout << "Here are the items you possess:" << std::endl;
		inventory_.printInfo();
	}


	std::cout << "Charges: " << charges_ << std::endl;
}

void Game::examine(const std::string& name)
{
	int i = currentRoom_->getItem(name);
	if (i != -1)
	{
		Item* item = currentRoom_->getItem(i);
		if (item->isAvailable())
		{
			std::cout << item->getClue() << std::endl;
			return;
		}
	}

	i = currentRoom_->getTrigger(name);
	if (i != -1)
	{
		Trigger* trigger = currentRoom_->getTrigger(i);
		std::cout << trigger->getClue() << std::endl;
		if (trigger->getAction() == T_EXAMINE)
		{
			currentRoom_->deleteTrigger(i);

			openItem(trigger->getEntityName());
		}
		return;
	}

	i = inventory_.getEntity(name);

	if (i != -1)
	{
		std::cout << inventory_.getEntity(i)->getClue() << std::endl;
		return;
	}

	std::cout << "You cannot examine " << name << "." << std::endl;
}

void Game::move(const std::string& name)
{
	int i = currentRoom_->getTrigger(name);
	if (i != -1)
	{
		Trigger* trigger = currentRoom_->getTrigger(i);

		if (trigger->getAction() == T_MOVE)
		{
			currentRoom_->deleteTrigger(i);
			std::cout << "You moved the " << name << ".\n";
			openExit(trigger->getEntityName());
			return;
		}
	}
	std::cout << "You cannot move " << name << "." << std::endl;
}

void Game::attack(const std::string& name)
{
	int i = currentRoom_->getNPC(name);

	if (i == -1)
	{
		std::cout << "You cannot attack " << name << ".\n";
		return;
	}

	NPC* attacked = currentRoom_->getNPC(i);

	if (!attacked->isAwake())
	{
		std::cout << "Come on, you've done enough damage already, stop." << std::endl;
		return;
	}

	if (!isInCombat_)
	{
		isInCombat_ = true;
		currentEnemy_ = attacked;
	}

	attack();
}

void Game::attack()
{
	int damage = dmg_;
	 
	if (squad_.isEmpty())
	{
		if (dmg_ > 0)
		{
			std::cout << "You really think you can take someone with bare hands?" << std::endl;
			return;
		}
		std::cout << "You attack him with your shard." << std::endl;
	}
	else
	{
		std::cout << "You and your squad attack him all at once." << std::endl;

		damage += squad_.getOverallDamage();
	}

	currentEnemy_->takeDamage(damage);
	
	if (currentEnemy_->isAwake())
	{
		std::cout << currentEnemy_->getName() << " strikes back." << std::endl;
		getAttacked();
		return;
	}


	if (currentEnemy_->getName() == "Guard Andrew")
	{
		std::cout << "You sneak out a cell key from his pocket." << std::endl;
		openItem("cell Key");
	}

	isInCombat_ = false;
	currentEnemy_ = nullptr;
}

void Game::getAttacked()
{
	if (squad_.isEmpty())
	{
		std::cout << "There is nobody to protect you, and you are extremely weak. You have no chance but to surrender." << std::endl;
		isRunning_ = false;
	}

	int who = rand() % sizeof(squad_);

	NPC* attackedMember = squad_.getEntity(who);

	attackedMember->takeDamage(currentEnemy_->damage());

	if (!attackedMember->isAwake())
	{
		squad_.deleteEntity(who);
		currentRoom_->addNPC(std::move(attackedMember));
	}
}

void Game::give(const std::string& item, const std::string& npc)
{
	int iItem = inventory_.getEntity(item);

	if (iItem == -1)
	{
		std::cout << "You do not have " << item << " to give." << std::endl;
		return;
	}

	Item* givenItem = inventory_.getEntity(iItem);

	int iNPC = currentRoom_->getNPC(npc);

	if (iNPC == -1)
	{
		std::cout << "There is no " << npc << " in the room." << std::endl;
		return;
	}

	NPC* npcToGive = currentRoom_->getNPC(iNPC);

	if (!npcToGive->isAwake())
	{
		std::cout << "What is the means of trying to give something to unconscious guy?" << std::endl;
		return;
	}

	Utils::setColor(14);
	std::cout << npcToGive->getName() << ": ";
	Utils::setColor(7);

	if (Utils::toCompare(npcToGive->requiredItem(), item))
	{
		std::cout << npcToGive->hasItemResponse() << std::endl;
		std::cout << "..." << std::endl << "..." << std::endl << "..." << std::endl;
		std::cout << "Andrew fell asleep, drowsy from smoking." << std::endl;
		npcToGive->setHP(0);
		inventory_.deleteEntity(iItem);
		std::cout << "You sneak out cell key from his pocket." << std::endl;
		openItem("Key");
		return;
	}
	else
	{
		std::cout << npcToGive->incorrectItemResponse() << std::endl;
		return;
	}
}

void Game::give(int item, const std::string& npc)
{
	Item* givenItem = inventory_.getEntity(item);

	int i = currentRoom_->getNPC(npc);

	if (i == -1)
	{
		std::cout << "There is no " << npc << " in the room." << std::endl;
		return;
	}

	NPC* npcToGive = currentRoom_->getNPC(i);

	Utils::setColor(14);
	std::cout << npcToGive->getName() << ": ";
	Utils::setColor(7);

	if (Utils::toCompare(npcToGive->requiredItem(), givenItem->getName()))
	{
		std::cout << npcToGive->hasItemResponse() << std::endl;
		std::cout << "..." << std::endl << "..." << std::endl << "..." << std::endl;
		std::cout << "Andrew fell asleep, drowsy from smoking." << std::endl;
		npcToGive->setHP(0);
		inventory_.deleteEntity(item);
		return;
	}
	else
	{
		std::cout << npcToGive->incorrectItemResponse() << std::endl;
		return;
	}
}

void Game::clone(const std::string& name)
{

	int i = currentRoom_->getNPC(name);

	NPC* npcToClone;

	if (i != -1)
	{
		npcToClone = currentRoom_->getNPC(i);
	}
	else {
		i = squad_.getEntity(name);
		if (i != -1)
		{
			npcToClone = squad_.getEntity(i);
		}
		else {
			std::cout << "You cannot clone " << name << ".\n";
			return;
		}
	}
	
	if (!npcToClone->canBeCloned())
	{
		std::cout << "You cannot clone " << name << ".\n";
		return;
	}

	std::string delimeter = " ";

	std::string oldName = npcToClone->getName();

	std::string newName;

	size_t pos = oldName.find(delimeter);

	if (pos != std::string::npos)
		newName = oldName.substr(pos + 1);
	else
		newName = oldName;

	NPC* clone = new NPC("Clone " + newName, npcToClone->damage(), npcToClone->getHitChance());

	charges_--;

	std::cout << "You make a full copy of " << npcToClone->getName() << ". Although it is a little bit more fragile and dumber." << std::endl;

	if (squad_.isFull())
	{
		std::cout << "Your squad is already a bit full though, so you cannot take this clone with you for now." << std::endl;
		currentRoom_->addNPC(std::move(clone));
	}
	else {
		std::cout << "Now this clone will follow you along until you leave them or they die." << std::endl;
		squad_.addEntity(std::move(clone));
	}
}

void Game::recruit(const std::string& name)
{
	int i = currentRoom_->getNPC(name);

	if (i == -1)
	{
		std::cout << "You cannot recruit " << name << ".\n";
		return;
	}

	NPC* npc = currentRoom_->getNPC(i);

	if (!npc->isAwake())
	{
		std::cout << "Why do you want to recruit an unconscious body?" << std::endl;
		return;
	}

	if (!npc->isRecrutable())
	{
		std::cout << "They would rather die than join you." << std::endl;
		return;
	}

	std::cout << npc->getName() << " joins your squad." << std::endl;
	currentRoom_->deleteNPC(i);
}

void Game::leave(const std::string& name)
{
	int i = squad_.getEntity(name);

	if (i == -1)
	{
		std::cout << name << " is not in your squad." << std::endl;
		return;
	}

	leave(i);
}

void Game::leave(int i)
{
	NPC* npc = squad_.getEntity(i);
	if (npc->canBeCloned())
	{
		std::cout << npc->getName() << " doesn't want to be left behind." << std::endl;
		return;
	}

	squad_.deleteEntity(i);
	currentRoom_->addNPC(std::move(npc));
	std::cout << "You leave him in this room to stand by." << std::endl;
}

void Game::open(const std::string& trigger, const std::string& key)
{
	int iTrigger = currentRoom_->getTrigger(trigger);

	if (iTrigger == -1)
	{
		std::cout << "You cannot open " << trigger << ".\n";
		return;
	}

	int iKey = inventory_.getEntity(key);

	if (iKey == -1)
	{
		std::cout << "You do not have " << key << ".\n";
		return;
	}

	open(iTrigger, iKey);
}

void Game::open(const std::string& trigger, int key)
{
	int i = currentRoom_->getTrigger(trigger);

	if (i == -1)
	{
		std::cout << "You cannot open " << trigger << ".\n";
		return;
	}

	open(i, key);
}

void Game::open(int iTrigger, int iKey)
{
	Trigger* trigger = currentRoom_->getTrigger(iTrigger);

	if (trigger->getAction() != T_OPEN)
	{
		std::cout << "You cannot open " << trigger->getName() << ".\n";
		return;
	}

	Item* key = inventory_.getEntity(iKey);

	if (!Utils::toCompare(key->getName(), trigger->getKey()))
	{
		std::cout << "You cannot open " << trigger->getName() << " with " << key->getName() << ".\n";
		return;
	}

	currentRoom_->deleteTrigger(iTrigger);

	openExit(trigger->getEntityName());

	std::cout << "You opened the " << trigger->getName();
}

void Game::openExit(const std::string& exit)
{
	currentRoom_->openExit(exit);
	rooms_[exit]->openExit(currentRoom_->getName());

	std::cout << "The way to " << exit << " has been opened." << std::endl;
}

void Game::openItem(const std::string& item)
{
	int iItem = currentRoom_->getItem(item);

	Item* openedItem = currentRoom_->getItem(iItem);

	openedItem->setAvailable();

	if (dmg_ == 0 && openedItem->getName() == "shard")
	{
		dmg_ = 1;
		std::cout << "Good, now you have a weapon." << std::endl;
		delete openedItem;
		currentRoom_->deleteItem(iItem);
		return;
	}

	if (inventory_.isFull())
	{
		std::cout << "You don't have enough space in your inventory to take it though." << std::endl;
		return;
	}

	currentRoom_->deleteItem(iItem);
	inventory_.addEntity(std::move(openedItem));
	std::cout << "You take " << openedItem->getName() << std::endl;
}

void Game::use(const std::string& key, const std::string& trigger)
{
	int iKey = inventory_.getEntity(key);

	if (iKey == -1)
	{
		std::cout << "You do not have " << key << " in your inventory." << std::endl;
		return;
	}

	use(iKey, trigger);
}

void Game::use(int key, const std::string& trigger)
{
	int iTrigger = currentRoom_->getTrigger(trigger);

	if (iTrigger == -1)
	{
		std::cout << "You cannot use this on " << trigger << ".\n";
		return;
	}

	use(key, iTrigger);
}

void Game::use(int iKey, int iTrigger)
{
	Trigger* trigger = currentRoom_->getTrigger(iTrigger);

	Item* item = inventory_.getEntity(iKey);

	if (!Utils::toCompare(trigger->getKey(), item->getName()))
	{
		std::cout << "You cannot use " << item->getName() << " on " << trigger->getName() << ".\n";
		return;
	}

	currentRoom_->deleteTrigger(iTrigger);

	if (trigger->getType() == T_ITEM)
	{
		openItem(trigger->getEntityName());
	}

	if (trigger->getType() == T_EXIT)
	{
		openExit(trigger->getEntityName());
		return;
	}
}

void Game::squad()
{
	if (squad_.isEmpty())
	{
		std::cout << "You have nobody by your side" << std::endl;
		return;
	}
	std::cout << "Here is your squad:" << std::endl;
	squad_.printInfo();
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

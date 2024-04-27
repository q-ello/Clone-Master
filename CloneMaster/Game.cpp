#include "Game.h"
#include <fstream>
#include <iostream>
#include <filesystem>

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
		if (inst.function != F_NONE)
		{
			updateState(inst);
		}
		else
		{
			std::cout << "Excuse you?\n";
		}
	}
}

void Game::dispose()
{
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
	default:
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
		for (const auto& [direction, name] : room->getExits())
		{
			json exitJson;
			exitJson["direction"] = DirectionsToString.at(direction);
			exitJson["name"] = name;
			exitsJson.push_back(exitJson);
		}
		roomJson.emplace("exits", exitsJson);
		roomsJson.push_back(roomJson);
	}
	j.emplace("rooms", roomsJson);

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
			newRoom->addExit(DirectionsToEnum.at(exitJson.at("direction")), exitJson.at("name"));
		}

		rooms_[name] = newRoom;
	}

	currentRoom_ = rooms_.at(data.at("current"));
}

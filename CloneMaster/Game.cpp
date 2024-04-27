#include "Game.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <iostream>

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
			newRoom->addExit(DirectionsMapped.at(exitJson.at("direction")), exitJson.at("name"));
		}

		rooms_[name] = newRoom;
	}

	currentRoom_ = rooms_.at(data.at("start"));
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
	default:
		break;
	}
}

void Game::go(const std::string& direction)
{
	bool canGo = true;
	Direction dir;
	if (direction.length() == 1)
	{
		switch (direction[0])
		{
		case 'n':
			dir = DirectionsMapped.at("north");
			break;
		case 'e':
			dir = DirectionsMapped.at("east");
			break;
		case 's':
			dir = DirectionsMapped.at("south");
			break;
		case 'w':
			dir = DirectionsMapped.at("west");
			break;
		case 'u':
			dir = DirectionsMapped.at("up");
			break;
		case 'd':
			dir = DirectionsMapped.at("down");
			break;
		default:
			canGo = false;
			break;
		}
	}
	else if (!DirectionsMapped.contains(direction))
	{
		canGo = false;
	}
	else 
	{
		dir = DirectionsMapped[direction];
	}

	if (canGo)
	{
		std::string id;
		if (currentRoom_->getExitId(dir, id))
		{
			currentRoom_ = rooms_[id];
			currentRoom_->printRoomInfo();
			return;
		}
	}
	std::cout << "You can't go that way.\n";
}

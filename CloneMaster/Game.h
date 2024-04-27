#pragma once

#ifndef _GAME_
#define _GAME_

#include <map>
#include <string>
#include "Room.h"
#include "Input.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Game
{
public:
	Game()
		:isRunning_{false},
		currentRoom_{nullptr}
	{};

	void play();

private:
	//load data 
	void initWorld();
	void run();
	void dispose();
	void printIntroduction();
	void updateState(Instruction instruction);
	void go(const std::string& direction);
	void save();
	void restore();
	void parseData(json data);

	std::map<std::string, Room*> rooms_;
	bool isRunning_;
	Room* currentRoom_;
};

#endif // !_GAME_
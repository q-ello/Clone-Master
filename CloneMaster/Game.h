#pragma once

#ifndef _GAME_
#define _GAME_

#include <map>
#include <string>
#include "Models/Room.h"
#include "Utilities/Input.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "Models/Store.h"

class Game
{
public:
	Game()
		:isRunning_{false},
		currentRoom_{nullptr},
		inventory_{},
		squad_{}
	{};

	void play();

private:
	//load data from data.json
	void initWorld();
	//run game
	void run();
	//delete game
	void dispose();
	void printIntroduction();
	//take player's input and parse it to update state with switch case
	void updateState(Instruction instruction);
	//go to another room
	void go(const std::string& direction);
	//save the progress into savefile.json
	void save();
	//restore the progress from savefile.json
	void restore();
	//helper to parse json data
	void parseData(json data);
	//help log
	void help();
	//put the item in inventory
	void take(std::string item);
	//look through inventory
	void printInventory();

	//the array of all rooms in the game
	std::map<std::string, Room*> rooms_;
	bool isRunning_;
	//the room the player is currently in
	Room* currentRoom_;
	Inventory inventory_;
	Squad squad_;
};

#endif // !_GAME_
#pragma once

#ifndef _GAME_
#define _GAME_

#include "stdafx.h"
#include "Models/Room.h"
#include "Utilities/Input.h"
#include "Models/Store.h"

class Game
{
public:
	Game()
		:isRunning_{ false },
		currentRoom_{ nullptr },
		inventory_{},
		squad_{},
		dmg_{ 0 },
		isInCombat_ {false},
		currentEnemy_ {nullptr}
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
	void parseData(const json& data);
	//help log
	void help();
	//put the item in inventory
	void take(const std::string& item);
	//drop item into the room
	void drop(const std::string& item);
	void drop(int i);
	//look through inventory
	void printInventory();
	//examine item in the room or your inventory
	void examine(const std::string& name);
	//move something
	void move(const std::string& name);
	//attack npc
	void attack(const std::string& name);
	void attack();
	//get attacked by npc
	void getAttacked();
	//give smth to npc
	void give(const std::string& item, const std::string& npc);
	void give(int item, const std::string& npc);
	//quit game
	void quit();

	//the array of all rooms in the game
	std::map<std::string, Room*> rooms_;
	bool isRunning_;
	//the room the player is currently in
	Room* currentRoom_;
	Inventory inventory_;
	Squad squad_;
	int dmg_;
	bool isInCombat_;
	NPC* currentEnemy_;
};

#endif // !_GAME_
#pragma once

#ifndef _ROOM_
#define _ROOM_

#include <string>
#include <vector>
#include "Directions.h"
#include <map>
#include <iostream>

class Room
{
public:
	Room(const std::string& name, const std::string& description)
		: name_{ name },
		description_{ description }
	{};

	~Room();

	void addExit(Direction direction, const std::string& room)
	{
		exits_[direction] = room;
	};

	void printRoomInfo();

	//get the name of the room we are going into
	bool getExitId(Direction dir, std::string& id);

	std::string getName() const
	{
		return name_;
	}

	std::string getDescription() const
	{
		return description_;
	}

	std::map<Direction, std::string> getExits() const
	{
		return exits_;
	}

private:
	std::string name_;
	std::string description_;
	std::map<Direction, std::string> exits_;
};

#endif // !_ROOM_

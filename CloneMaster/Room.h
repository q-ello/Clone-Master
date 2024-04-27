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

	void addExit(Direction direction, const std::string& room)
	{
		exits_[direction] = room;
	};

	void printRoomInfo();

	bool getExitId(Direction dir, std::string& id);

private:
	std::string name_;
	std::string description_;
	std::map<Direction, std::string> exits_;
};

#endif // !_ROOM_

#pragma once

#ifndef _ROOM_
#define _ROOM_

#include <string>
#include <vector>
#include "../Utilities/Directions.h"
#include <map>
#include <iostream>
#include "Item.h"

struct Exit {
	std::string name;
	bool available;
};

class Room
{
public:
	Room(const std::string& name, const std::string& description)
		: name_{ name },
		description_{ description },
		items_{}
	{};

	~Room();

	void addExit(Direction direction, const std::string& room, bool available = true)
	{
		exits_[direction] = Exit{ room, available };
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

	std::map<Direction, Exit> getExits() const
	{
		return exits_;
	}

	std::vector<Item*> getItems() const
	{
		return items_;
	}

	void addItem(Item* item)
	{
		items_.push_back(std::move(item));
	}

	Item* getItemByName(std::string& name);

private:
	std::string name_;
	std::string description_;
	std::map<Direction, Exit> exits_;
	std::vector<Item*> items_;
};

#endif // !_ROOM_

#pragma once

#ifndef _ROOM_
#define _ROOM_

#include "../stdafx.h"
#include "../Utilities/Directions.h"
#include "Item.h"
#include "Trigger.h"
#include "NPC.h"

struct Exit {
	std::string name;
	bool available;
};

class Room
{
public:
	Room(const std::string& name, const std::string& description)
		: name_{ name }
		, description_{ description }
		, items_{}
		, triggers_{}
		, npcs_{}
	{};

	~Room();

	void addExit(Direction direction, const std::string& room, bool available = true)
	{
		exits_[direction] = Exit{ room, available };
	};

	void printRoomInfo();

	//get the name of the room we are going into
	bool getExitId(Direction dir, std::string& id);

	//get name of the room
	std::string getName() const
	{
		return name_;
	}
	//get room's description
	std::string getDescription() const
	{
		return description_;
	}
	//get room's exits
	std::map<Direction, Exit> getExits() const
	{
		return exits_;
	}
	//get room's items
	std::vector<Item*> getItems() const
	{
		return items_;
	}

	//get room's triggers
	std::vector<Trigger*> getTriggers() const
	{
		return triggers_;
	}

	//add item to the room
	void addItem(Item* item)
	{
		items_.push_back(std::move(item));
	}
	//get index of item in the room
	int getItemByName(const std::string& name);

	//check if item is available
	bool itemIsAvailable(int i)
	{
		return items_[i]->isAvailable();
	}

	//get item from the room
	Item* getItem(int i);

	//get item's clue
	void getItemClue(int i);

	//add trigger to the room
	void addTrigger(Trigger* trigger)
	{
		triggers_.push_back(std::move(trigger));
	}

	//get Trigger by name
	int getTriggerByName(const std::string& name);

	//get Trigger's clue
	void getTriggerClue(int i);

	//get trigger's action
	TriggerAction getTriggerAction(int i);

	//trigger itemTrigger lmao
	Item* triggerItem(int i, bool canTake);

	//get name of openable exit
	std::string getTriggerEntity(int i);

	//openExit
	void openExit(const std::string& exitName );

	//addNPC to the room
	void addNPC(NPC* npc)
	{
		npcs_.push_back(std::move(npc));
	}

	std::vector<NPC*> getNPCs() const
	{
		return npcs_;
	}

	//get npc in the room
	NPC* getNPCByName(const std::string& name);

	//delete npc from the room
	void deleteNPC(int i);

	//show hostile npc and greet 
	NPC* isDangerous();

private:
	std::string name_;
	std::string description_;
	std::map<Direction, Exit> exits_;
	std::vector<Item*> items_;
	std::vector<Trigger*> triggers_;
	std::vector<NPC*> npcs_;
};

#endif // !_ROOM_

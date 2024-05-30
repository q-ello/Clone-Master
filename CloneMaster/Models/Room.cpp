#include "Room.h"
#include "../Utilities/Utils.h"

Room::~Room()
{
	exits_.clear();
	items_.clear();
	npcs_.clear();
}

void Room::printRoomInfo()
{
	Utils::setColor(11);
	std::cout << name_ << std::endl <<std::endl;
	Utils::setColor(7);
	std::cout << description_ << std::endl;

	for (Item* item : items_)
	{
		if (item->isAvailable())
		{
			std::cout << item->getDescription() << std::endl;
		}
	}

	for (NPC* npc : npcs_)
	{
		std::cout << npc->getDescription() << std::endl;
	}
}

bool Room::getExitId(Direction dir, std::string& id)
{
	if (exits_.contains(dir))
	{
		Exit exit = exits_.at(dir);
		if (exit.available)
		{
			id = exit.name;
			return true;
		}

		std::cout << "The way is blocked.\n";
		return false;
	}

	std::cout << "There is no way in that direction.\n";
	return false;
}

int Room::getItem(const std::string& name)
{
	int index = -1;
	for (auto it = items_.begin(); it != items_.end(); it++)
	{
		if (Utils::toCompare(name, (*it)->getName()))
		{
			index = static_cast<int>(it - items_.begin());
			break;
		}
	}
	return index;
}

Item* Room::getItem(int i)
{
	return items_[i];;
}

void Room::deleteItem(int i)
{
	items_.erase(i + items_.begin());
}


int Room::getTrigger(const std::string& name)
{
	int index = -1;
	for (auto it = triggers_.begin(); it != triggers_.end(); it++)
	{
		if (Utils::toCompare(name, (*it)->getName()))
		{
			index = static_cast<int>(it - triggers_.begin());
			break;
		}
	}
	return index;
}

Trigger* Room::getTrigger(int i)
{
	return triggers_[i];
}

void Room::deleteTrigger(int i)
{
	triggers_.erase(i + triggers_.begin());
}

void Room::openExit(const std::string& exitName)
{
	for (auto& [dir, exit] : exits_)
	{
		if (exit.name == exitName)
		{
			exit.available = true;
		}
	}
}

int Room::getNPC(const std::string& name)
{
	int index = -1;
	for (auto it = npcs_.begin(); it != npcs_.end(); it++)
	{
		if (Utils::toCompare(name, (*it)->getName()))
		{
			index = static_cast<int>(it - npcs_.begin());
			break;
		}
	}

	return index;
}

NPC* Room::getNPC(int i)
{
	return npcs_[i];
}

void Room::deleteNPC(int i)
{
	npcs_.erase(npcs_.begin() + i);
}

NPC* Room::isDangerous()
{
	NPC* possibleEnemy = nullptr;
	for (auto& npc : npcs_)
	{
		if (npc->isAwake())
		{
			Utils::setColor(14);
			std::cout << npc->getName() << ": ";
			Utils::setColor(7);
			std::cout << npc->getGreeting() << std::endl;
		}

		if (npc->getName() != "Guard Andrew" && npc->isAwake() && !npc->isRecrutable())
		{
			possibleEnemy = npc;
		}
	}
	return possibleEnemy;
}
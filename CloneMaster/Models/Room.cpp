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

int Room::getItemByName(const std::string& name)
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
	Item* itemptr = items_[i];
	items_.erase(items_.begin() + i);
	return itemptr;
}

void Room::getItemClue(int i)
{
	std::cout << items_[i]->getClue() << std::endl;
}

int Room::getTriggerByName(const std::string& name)
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

void Room::getTriggerClue(int i)
{
	std::cout << triggers_[i]->getClue() << std::endl;
}

TriggerAction Room::getTriggerAction(int i)
{
	return triggers_[i]->getAction();
}

Item* Room::triggerItem(int triggerInd, bool takeable)
{
	std::string entName = getTriggerEntity(triggerInd);
	int itemInd = getItemByName(entName);
	items_[itemInd]->setAvailable();
	if (!takeable)
	{
		return nullptr;
	}

	return getItem(itemInd);
}

std::string Room::getTriggerEntity(int i)
{
	std::string entityName = triggers_[i]->getEntityName();
	triggers_.erase(triggers_.begin() + i);

	return entityName;
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

NPC* Room::getNPCByName(const std::string& name)
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
	if (index == -1)
		return nullptr;

	return npcs_[index];
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
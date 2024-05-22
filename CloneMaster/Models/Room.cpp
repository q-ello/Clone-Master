#include "Room.h"
#include "../Utilities/Utils.h"

Room::~Room()
{
	exits_.clear();
	items_.clear();
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
	std::string entName = triggers_[triggerInd]->getEntityName();
	int itemInd = getItemByName(entName);
	items_[itemInd]->setAvailable();
	if (!takeable)
	{
		return nullptr;
	}

	triggers_.erase(triggers_.begin() + triggerInd);

	return getItem(itemInd);
}
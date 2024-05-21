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

Item* Room::getItemByName(std::string& name)
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
	if (index == -1)
	{
		return nullptr;
	}

	Item* itemptr = items_[index];
	items_.erase(items_.begin() + index);
	return itemptr;
}

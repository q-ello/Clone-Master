#include "Room.h"

void Room::printRoomInfo()
{
	std::cout << name_ << std::endl;
	std::cout << description_ << std::endl;
}

bool Room::getExitId(Direction dir, std::string& id)
{
	if (exits_.contains(dir))
	{
		id = exits_.at(dir);
		return true;
	}

	return false;
}

#pragma once

#ifndef _ITEM_
#define _ITEM_

#include <string>

class Item
{
public:
	Item(const std::string& name, const std::string& description, const std::string& clue, bool available)
		: name_{ name },
		description_{ description },
		clue_{ clue },
		available_{ available }
	{}

	std::string getName() const
	{
		return name_;
	}

	bool isAvailable()
	{
		return available_;
	}

	std::string getDescription() const
	{
		return description_;
	}

	std::string getClue() const
	{
		return clue_;
	}

private:
	std::string name_;
	std::string description_;
	std::string clue_;
	bool available_;
};

#endif // !_ITEM_

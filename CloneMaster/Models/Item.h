#pragma once

#ifndef _ITEM_
#define _ITEM_

#include "../stdafx.h"

class Item
{
public:
	Item(const std::string& name, const std::string& description, const std::string& clue, bool available = true)
		: name_{ name },
		description_{ description },
		clue_{ clue },
		available_{ available }
	{}

	~Item();

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

	void setAvailable()
	{
		available_ = true;
	}

private:
	std::string name_;
	std::string description_;
	std::string clue_;
	bool available_;
};

#endif // !_ITEM_

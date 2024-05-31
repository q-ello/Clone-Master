#pragma once

#ifndef _NPC_

#define _NPC_

#include "../stdafx.h"

class NPC
{
public:
	NPC(const std::string& name,
		int dmg,
		int hitChance,
		const std::string& inRoomAwake = "",
		const std::string& inRoomUnconscious = "",
		const std::string& incorrectItemResponse = "",
		const std::string& requiredItem = "",
		const std::string& hasItemResponse = "",
		int HP = 1,
		const std::string& greeting = "Argh...",
		bool canBeCloned = false,
		bool isRecrutable = true)
	;

	~NPC() {};
	
	//oh no, he's damaged!
	void takeDamage(int dmg);

	int damage()
	{
		return dmg_;
	}
	
	std::string getGreeting() const
	{
		return greeting_;
	}

	std::string getName() const
	{
		return name_;
	}

	std::string getDescription() const;

	int getHP()
	{
		return HP_;
	}

	void setHP(int hp)
	{
		HP_ = hp;
	}

	int getHitChance()
	{
		return hitChance_;
	}

	bool canBeCloned()
	{
		return canBeCloned_;
	}

	bool isRecrutable()
	{
		return isRecrutable_;
	}

	std::string getDescriptionAwake() const
	{
		return inRoomAwake_;
	}

	std::string getDescriptionUnconscious() const
	{
		return inRoomUnconscious_;
	}

	std::string incorrectItemResponse() const
	{
		return incorrectItemResponse_;
	}

	std::string requiredItem() const
	{
		return requiredItem_;
	}

	std::string hasItemResponse() const
	{
		return hasItemResponse_;
	}

	bool isAwake()
	{
		return HP_ > 0;
	}

private:
	std::string name_;
	int HP_;
	int dmg_;
	int hitChance_;
	bool canBeCloned_;
	bool isRecrutable_;
	std::string inRoomAwake_;
	std::string inRoomUnconscious_;
	std::string greeting_;
	std::string incorrectItemResponse_;
	std::string requiredItem_;
	std::string hasItemResponse_;
};

#endif // !_CHARACTER_
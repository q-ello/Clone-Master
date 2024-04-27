#pragma once

#ifndef _CHARACTER_

#define _CHARACTER_


#include <string>

//the difference between clones and others: mind_ = 0; some enemies can become allies, so I guess it's okay to do it in one class
class Character
{
public:
	Character();
	~Character();
	//TODO: getters/setters

	//clone the character
	void* clone()
	{
		isCloned_ = true;
	}

	//TODO: lowering HP
	void takeDamage();

	//TODO: returned int is dmg
	int attack();

	//TODO: do dialogues
	std::string talk();

	//TODO: equip clones
	void equip();

	//TODO: unequip clones
	void enequip();

	//TODO: heal clones
	void heal();

private:
	int HP_;
	int mind_;
	int dex_;
	int atk_;
	int hostility;
	bool isCloned_;
};

#endif // !_CHARACTER_
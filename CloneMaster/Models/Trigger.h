#pragma once

#ifndef _TRIGGER_

#define _TRIIGER_

#include "../stdafx.h"

enum TriggerAction
{
	T_OPEN,
	T_MOVE,
	T_EXAMINE,
	T_USE,
	T_NONE
};

enum TriggerType
{
	T_ITEM,
	T_EXIT,
	T_DUMMY
};

class Trigger
{
public:
	Trigger(
		const std::string& name, 
		const std::string& clue, 
		const std::vector<std::string>& entityName = {},
		TriggerAction action = T_NONE,
		const std::string& neededItem = "",
		TriggerType type = T_DUMMY
	)
		: name_ {name}
		, clue_ {clue}
		, entityName_ {entityName}
		, action_{ action }
		, neededItem_ {neededItem}
		, type_ {type}
	{};

	~Trigger() {};

	std::string getName() const
	{
		return name_;
	}

	std::string getClue() const
	{
		return clue_;
	}

	TriggerAction getAction() {
		return action_;
	}

	std::vector<std::string> getEntitiesName() const
	{
		return entityName_;
	}

	TriggerType getType() {
		return type_;
	}

	std::string getKey() const
	{
		return neededItem_;
	}

private:
	std::string name_;
	std::string clue_;
	std::vector<std::string> entityName_;
	TriggerAction action_;
	std::string neededItem_;
	TriggerType type_;
};

static std::map<std::string, TriggerAction> TriggerActionsToEnum
{
	{"open", T_OPEN},
	{"move", T_MOVE},
	{"examine", T_EXAMINE},
	{"use", T_USE},
	{"none", T_NONE}
};


static std::map<std::string, TriggerType> TriggerTypesToEnum
{
	{"exit", T_EXIT},
	{"item", T_ITEM},
	{"dummy", T_DUMMY}
};


static std::map<TriggerAction, std::string> TriggerActionsToString
{
	{T_OPEN, "open"},
	{T_MOVE, "move"},
	{T_EXAMINE, "examine"},
	{T_USE, "use"},
	{T_NONE, "none"}
};


static std::map<TriggerType, std::string> TriggerTypesToString
{
	{T_EXIT, "exit"},
	{T_ITEM, "item"},
	{T_DUMMY, "dummy"}
};

#endif // !_TRIGGER_


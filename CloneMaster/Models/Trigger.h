#pragma once

#ifndef _TRIGGER_

#define _TRIIGER_

#include "../stdafx.h"

enum TriggerAction
{
	T_OPEN,
	T_MOVE,
	T_EXAMINE,
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
		const std::string& entityName = "",
		TriggerAction action = T_NONE,
		const std::string& neededItem = "",
		TriggerType type = T_DUMMY
	)
		: name_ {name}
		, clue_ {clue}
		, entityName_ {entityName}
		, action_{ action }
		, neededItem_ {neededItem}
	{}

	~Trigger();

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

	std::string getEntityName() const
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

protected:
	std::string name_;
	std::string clue_;
	std::string entityName_;
	TriggerAction action_;
	std::string neededItem_;
	TriggerType type_;
};

static std::map<std::string, TriggerAction> TriggerActionsToEnum
{
	{"open", T_OPEN},
	{"move", T_MOVE},
	{"examine", T_EXAMINE}
};


static std::map<std::string, TriggerType> TriggerTypesToEnum
{
	{"exit", T_EXIT},
	{"item", T_ITEM}
};


static std::map<TriggerAction, std::string> TriggerActionsToString
{
	{T_OPEN, "open"},
	{T_MOVE, "move"},
	{T_EXAMINE, "examine"}
};


static std::map<TriggerType, std::string> TriggerTypesToString
{
	{T_EXIT, "exit"},
	{T_ITEM, "item"}
};

#endif // !_TRIGGER_


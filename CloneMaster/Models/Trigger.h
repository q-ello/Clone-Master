#pragma once

#ifndef _TRIGGER_

#define _TRIIGER_

#include "../stdafx.h"

class Trigger
{
public:
	//TODO: make different triggers when you interact with the trigger correctly
	void trigger();
private:
	std::string name_;
	bool isTriggered();
	std::string neededItem;
};

#endif // !_TRIGGER_

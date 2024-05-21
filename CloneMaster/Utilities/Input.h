#pragma once

#ifndef _INPUT_
#define _INPUT_

#include "../stdafx.h"
#include "Function.h"

struct Instruction {
	Function function;
	std::string goal;
	std::string object;
};

class Input
{
public:
	//get user's input, divide it on words
	static Instruction ReadUser();
	static std::string GetInput();

private:
	//parse user's command
	static void DetermineCommand(const std::vector<std::string>& command, int n, Instruction& inst);
};

#endif // !_INPUT_



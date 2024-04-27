#pragma once

#ifndef _INPUT_
#define _INPUT_

#include <string>
#include "Function.h"
#include <vector>

struct Instruction {
	Function function;
	std::string goal;
	std::string object;
};

class Input
{
public:
	static Instruction ReadUser();
	static std::string GetInput();

private:
	static void DetermineCommand(const std::vector<std::string>& command, int n, Instruction& inst);
};

#endif // !_INPUT_



#include <iostream>
#include <sstream>

#include "Input.h"
#include "Utils.h"

Instruction Input::ReadUser()
{
	Instruction inst;

	std::string input = GetInput();

	Utils::toLowerAndTrim(input);

	std::vector<std::string> inputVec;
	std::string delimiter = " ";

	size_t pos = 0;
	int n = 0;
	std::string token;
	while ((pos = input.find(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		inputVec.push_back(token);
		n++;
		input.erase(0, pos + delimiter.length());
	}
	inputVec.push_back(input);
	n++;

	DetermineCommand(inputVec, n, inst);

	return inst;
}

std::string Input::GetInput()
{
	std::string input;
	std::getline(std::cin, input);
	return input;
}

void Input::DetermineCommand(const std::vector<std::string>& command, int n, Instruction& inst)
{
	if (n <= 2 && command[0] == "go") {
		if (n == 2)
		{
			inst.function = F_GO;
			inst.goal = command[1];
			return;
		}
		else
		{
			std::cout << "Where do you wanna go?\n>";
			std::string direction;
			std::getline(std::cin, direction);
			inst.function = F_GO;
			inst.goal = direction;
			return;
		}
	}

	if (n == 1 && command[0] == "n" || command[0] == "north")
	{
		inst.function = F_GO;
		inst.goal = "north";
		return;
	}

	if (n == 1 && command[0] == "e" || command[0] == "east")
	{
		inst.function = F_GO;
		inst.goal = "east";
		return;
	}

	if (n == 1 && command[0] == "s" || command[0] == "south")
	{
		inst.function = F_GO;
		inst.goal = "south";
		return;
	}

	if (n == 1 && command[0] == "w" || command[0] == "west")
	{
		inst.function = F_GO;
		inst.goal = "west";
		return;
	}

	if (n == 1 && command[0] == "d" || command[0] == "down")
	{
		inst.function = F_GO;
		inst.goal = "down";
		return;
	}

	if (n == 1 && command[0] == "u" || command[0] == "up")
	{
		inst.function = F_GO;
		inst.goal = "up";
		return;
	}

	if (n == 1 && command[0] == "i" || command[0] == "inventory") 
	{
		inst.function = F_INVENTORY;
		return;
	}

	if (n == 1 && command[0] == "save")
	{
		inst.function = F_SAVE;
		return;
	}

	if (n == 1 && command[0] == "restore")
	{
		inst.function = F_RESTORE;
		return;
	}

	/*if (inputVec[0] == "talk") != std::string::npos) {
		return FUNCTION_TALK;
	}
	else if (lower.find("give") != std::string::npos) {
		return FUNCTION_GIVE;
	}
	else if (lower.find("take") != std::string::npos) {
		return FUNCTION_TAKE;
	}
	else if (lower.find("drop") != std::string::npos) {
		return FUNCTION_DROP;
	}
	else if (lower.find("help") != std::string::npos || lower.find("?") != std::string::npos) {
		return FUNCTION_HELP;
	}
	else if (lower.find("view room") != std::string::npos) {
		return FUNCTION_VIEW_ROOM;
	}
	else if (lower.find("exit") != std::string::npos) {
		return FUNCTION_EXIT;
	}
	else if (lower.find("examine") != std::string::npos) {
		return FUNCTION_EXAMINE;
	}*/
	inst.function = F_NONE;
}
#include "Utils.h"
#include "Input.h"

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
		inst.function = F_GO;
		if (n == 2)
		{
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

	if (n == 1 && (command[0] == "n" || command[0] == "north"))
	{
		inst.function = F_GO;
		inst.goal = "north";
		return;
	}

	if (n == 1 && (command[0] == "e" || command[0] == "east"))
	{
		inst.function = F_GO;
		inst.goal = "east";
		return;
	}

	if (n == 1 && (command[0] == "s" || command[0] == "south"))
	{
		inst.function = F_GO;
		inst.goal = "south";
		return;
	}

	if (n == 1 && (command[0] == "w" || command[0] == "west"))
	{
		inst.function = F_GO;
		inst.goal = "west";
		return;
	}

	if (n == 1 && (command[0] == "d" || command[0] == "down"))
	{
		inst.function = F_GO;
		inst.goal = "down";
		return;
	}

	if (n == 1 && (command[0] == "u" || command[0] == "up"))
	{
		inst.function = F_GO;
		inst.goal = "up";
		return;
	}

	if (n == 1 && (command[0] == "i" || command[0] == "inventory")) 
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

	if (n <= 3 && command[0] == "talk") {
		std::string goal = "";
		inst.function = F_TALK;
		if (n == 1) {
			std::cout << "Who do you wanna talk to?";
			std::getline(std::cin, goal);
			inst.goal = goal;
			return;
		}
		if (command[1] != "to" && command[1] != "with")
		{
			inst.goal = command[1];
			return;
		}
		inst.goal = command[2];
		return;
	}

	if (n == 1 && (command[0] == "look" || command[0] == "l"))
	{
		inst.function = F_LOOK;
		return;
	}

	if (n == 1 && (command[0] == "help" || command[0] == "?"))
	{
		inst.function = F_HELP;
		return;
	}

	if (n <= 2 && command[0] == "take")
	{
		inst.function = F_TAKE;
		std::string goal = "";
		if (n == 1)
		{
			std::cout << "What do you wanna take?\n";
			std::getline(std::cin, goal);
			inst.goal = goal;
			return;
		}
		inst.goal = command[1];
		return;
	}

	if (n <= 3 && command[0] == "pick")
	{
		inst.function = F_TAKE;
		std::string goal = "";
		if (n == 1)
		{
			std::cout << "What do you wanna pick up?\n";
			std::getline(std::cin, goal);
			inst.goal = goal;
			return;
		}
		if (command[1] != "up")
		{
			inst.goal = command[1];
			return;
		}
		inst.goal = command[2];
		return;
	}

	if (n <= 2 && command[0] == "drop")
	{
		inst.function = F_DROP;
		std::string goal = "";
		if (n == 1)
		{
			std::cout << "What do you wanna drop?\n";
			std::getline(std::cin, goal);
			inst.goal = goal;
			return;
		}
		inst.goal = command[1];
		return;
	}

	if (n == 1 && command[0] == "quit")
	{
		inst.function = F_QUIT;
		return;
	}
	//TODO examine
	//TODO clone
	//TODO leave
	//TODO equip
	//TODO unequip
	inst.function = F_NONE;
}
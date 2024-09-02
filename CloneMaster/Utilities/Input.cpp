#include "Utils.h"
#include "Input.h"

Instruction Input::ReadUser()
{
	Instruction inst;

	std::string input = GetInput();

	std::string trimmedInput = Utils::toLowerAndTrim(input);

	std::vector<std::string> inputVec;
	std::string delimiter = " ";

	size_t pos = 0;
	int n = 0;
	std::string token;
	while ((pos = trimmedInput.find(delimiter)) != std::string::npos) {
		token = trimmedInput.substr(0, pos);
		inputVec.push_back(token);
		n++;
		trimmedInput.erase(0, pos + delimiter.length());
	}
	inputVec.push_back(trimmedInput);
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
		if (n == 1)
		{
			return;
		}
		inst.goal = command[1];
		return;
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

	if (n <= 3 && command[0] == "take")
	{
		inst.function = F_TAKE;
		if (n == 1)
		{
			std::cout << "What do you wanna take?\n";
			std::getline(std::cin, inst.goal);
			return;
		}
		inst.goal = command[1];

		if (n == 3)
			inst.goal += " " + command[2];

		return;
	}

	if (n <= 3 && command[0] == "drop")
	{
		inst.function = F_DROP;
		if (n == 1)
			return;
		inst.goal = command[1];

		if (n == 3)
		{
			inst.goal += " " + command[2];
		}
		return;
	}

	if (n == 1 && command[0] == "quit")
	{
		inst.function = F_QUIT;
		return;
	}

	if (n <= 3 && command[0] == "examine")
	{
		inst.function = F_EXAMINE;
		if (n == 1)
		{
			std::cout << "What do you want to examine?" << std::endl;
			std::getline(std::cin, inst.goal);
			return;
		}
		inst.goal = command[1];

		if (n == 3)
			inst.goal += " " + command[2];
		return;
	}

	if (n <= 3 && command[0] == "move")
	{
		inst.function = F_MOVE;
		if (n == 1)
		{
			std::cout << "What do you want to move?" << std::endl;
			std::getline(std::cin, inst.goal);
			return;
		}

		inst.goal = command[1];
		if (n == 3)
			inst.goal += " " + command[2];
		return;
	}

	if (n <= 3 && command[0] == "attack")
	{
		inst.function = F_ATTACK;
		if (n == 1)
		{
			return;
		}

		inst.goal = command[1];

		if (n == 3)
			inst.goal += " " + command[2];
		return;
	}

	if (n <= 6 && command[0] == "give")
	{
		inst.function = F_GIVE;
		if (n == 1)
		{
			return;
		}

		int i = 1;

		for (; i != n && command[i] != "to"; i++)
			inst.goal += " " + command[i];

		if (n == i)
		{
			std::cout << "Whom do you want to give it to?" << std::endl;
			std::getline(std::cin, inst.object);
			return;
		}

		for (++i; i != n; i++)
			inst.object += " " + command[i];

		return;
	}

	if (n <= 3 && command[0] == "clone")
	{
		inst.function = F_CLONE;
		if (n == 1)
		{
			std::cout << "Who do you want to clone?" << std::endl;
			std::getline(std::cin, inst.goal);
			return;
		}
		inst.goal = command[1];

		if (n == 3)
			inst.goal += " " + command[2];
		return;
	}

	if (n <= 6 && command[0] == "open")
	{
		inst.function = F_OPEN;
		if (n == 1)
		{
			std::cout << "What do you want to open?" << std::endl;
			std::getline(std::cin, inst.goal);
			return;
		}

		int i = 1;

		for (;  i < n && command[i] != "with"; i++)
			inst.goal += " " + command[i];

		if (n == i)
			return;

		for (++i; i != n; i++)
			inst.object += " " + command[i];

		return;
	}

	if (n <= 6 && command[0] == "use")
	{
		inst.function = F_USE;
		if (n == 1)
		{
			return;
		}

		int i = 1;

		for (; i != n && command[i] != "on"; i++)
			inst.object += " " + command[i];

		if (n == i)
		{
			std::cout << "What do you want to use it on?" << std::endl;
			std::getline(std::cin, inst.goal);
		}

		for (++i; i != n; i++)
			inst.goal += " " + command[i];

		return;
	}

	if (n <= 3 && command[0] == "recruit")
	{
		inst.function = F_RECRUIT;

		if (n == 1)
		{
			std::cout << "Who do you want to recruit?" << std::endl;
			std::getline(std::cin, inst.goal);
			return;
		}

		inst.goal = command[1];

		if (n == 3)
			inst.goal += " " + command[2];

		return;
	}

	if (n <= 3 && command[0] == "leave")
	{
		inst.function = F_LEAVE;

		if (n == 1)
			return;

		inst.goal = command[1];

		if (n == 3)
			inst.goal += " " + command[2];

		return;
	}

	if (n == 1 && command[0] == "squad")
	{
		inst.function = F_SQUAD;
		return;
	}

	inst.function = F_NONE;
}
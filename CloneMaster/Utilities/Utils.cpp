#include "Utils.h"

std::string Utils::toLower(const std::string& s)
{
	std::string lower = "";
	std::for_each(s.begin(), s.end(), [&lower](unsigned char ch) {
		lower += std::tolower(ch);
		});
	return lower;
}

std::string Utils::toLowerAndTrim(const std::string& s)
{
	if (s.size() > 0)
	{
		std::string lowS = toLower(s);
		lowS.erase(lowS.begin(), std::find_if(lowS.begin(), lowS.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));

		lowS.erase(std::find_if(lowS.rbegin(), lowS.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), lowS.end());
		return lowS;
	}
	return s;
}

bool Utils::toCompare(const std::string& a, const std::string& b)
{
	std::string lowA = toLowerAndTrim(a);
	std::string lowB = toLower(b);
	std::string delimeter = " ";
	size_t pos = lowB.find(delimeter);
	if (pos != std::string::npos)
	{
		lowB = lowB.substr(pos);
	}
	return lowA == lowB;
}

void Utils::setColor(int col)
{
	SetConsoleTextAttribute(hOut_, col);
}

COORD Utils::getCoords()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hOut_, &csbi);
	return csbi.dwCursorPosition;
}

void Utils::gotoxy(int x, int y)
{
	COORD c;
	
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(hOut_, c);
}

void Utils::showCursor(bool show)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut_, &cursorInfo);
	cursorInfo.bVisible = show;
	SetConsoleCursorInfo(hOut_, &cursorInfo);
}

int Utils::menu(std::vector<std::string> options)
{
	showCursor(false);

	int counter = 0;
	char key;

	int n = static_cast<int>(options.size());

	COORD currentPos = getCoords();

	for (; currentPos.Y >= 30 - n; currentPos.Y -= 1)
	{
		std::cout << std::endl;
	}

	while (true)
	{
		for (int i = 0; i < n; i++)
		{
			setColor(i == counter ? 8 : 7);
			gotoxy(currentPos.X + 5, currentPos.Y + i);
			std::string name = options[i];
			std::cout << options[i] << std::endl;
		}

		key = _getch();

		if (key == 72)
			counter = (counter - 1 + n) % n;

		if (key == 80)
			counter = (counter + 1) % n;

		if (key == 13)
		{
			std::cout << std::endl;
			showCursor(true);
			setColor(7);
			if (counter == n - 1)
				std::cout << "Nothing happened." << std::endl;
			return counter;
		}
	}
}

HANDLE Utils::hOut_ = GetStdHandle(STD_OUTPUT_HANDLE);

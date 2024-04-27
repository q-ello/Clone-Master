#pragma once

#ifndef _UTILS_
#define _UTILS_

#include <string>

enum Colors {
	COLORS_BLACK = 30,
	COLORS_RED = 31,
	COLORS_GREEN = 32,
	COLORS_YELLOW = 33,
	COLORS_BLUE = 34,
	COLORS_MAGENTA = 35,
	COLORS_CYAN = 36,
	COLORS_LIGHT_GRAY = 37,
	COLORS_DARK_GRAY = 38,
	COLORS_WHITE = 39,
};

class Utils
{
public:
	static std::string toLower(const std::string& s);
	/* Converts a string to lower case and trims it*/
	static void toLowerAndTrim(std::string& s);
	/* Compares two strings and returns true if they are the same */
	static bool toCompare(std::string& a, std::string b);
	/*TODO: set the color for some strings*/
	static std::string GetColor(Colors color);
};


#endif // !_UTILS_


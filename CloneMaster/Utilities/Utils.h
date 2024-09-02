#pragma once

#ifndef _UTILS_
#define _UTILS_

#include "../stdafx.h"

class Utils
{
public:
	/* Converts a string to lower case and trims it*/
	static std::string toLowerAndTrim(const std::string& s);
	/* Compares two strings and returns true if they are the same */
	static bool toCompare(const std::string& a, const std::string& b);
	//sets another color to the consol
	static void setColor(int color);
	//yey menu options!
	static int menu(std::vector<std::string> options);
	//helping to parse json
	static const std::string findJsonString(std::string query, json jsonPart)
	{
		std::string dummy = "";
		auto it = jsonPart.find(query);
		
		if (it != jsonPart.end() && (*it).is_string())
		{
			dummy = *it;
		}

		return dummy;
	}

	static const std::vector<std::string> findJsonVector(std::string query, json jsonPart)
	{
		std::vector<std::string> dummy{};
		auto it = jsonPart.find(query);

		if (it != jsonPart.end() && (*it).is_array())
		{
			dummy = *it;
		}
		else
		{
			dummy.push_back(*it);
		}

		return dummy;
	}

	static const int findJsonInt(std::string query, json jsonPart)
	{
		int dummy = 0;
		auto it = jsonPart.find(query);

		if (it != jsonPart.end() && (*it).is_number())
		{
			dummy = *it;
		}

		return dummy;
	}

	static const int findJsonBool(std::string query, json jsonPart)
	{
		bool dummy = false;
		auto it = jsonPart.find(query);

		if (it != jsonPart.end() && (*it).is_boolean())
		{
			dummy = *it;
		}

		return dummy;
	}

private:
	static HANDLE hOut_;
	static std::string toLower(const std::string& s);
	//gets coords of text
	static COORD getCoords();
	//set the position of the next text
	static void gotoxy(int x, int y);
	//hide or show cursor
	static void showCursor(bool show);
};


#endif // !_UTILS_


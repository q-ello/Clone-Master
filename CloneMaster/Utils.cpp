#include "Utils.h"

#include <locale>
#include <map>
#include <algorithm> 
#include <cctype>

void Utils::toLower(std::string& s)
{
	std::for_each(s.begin(), s.end(), [](unsigned char ch) {
		return std::tolower(ch);
		});
}

void Utils::toLowerAndTrim(std::string& s)
{
	if (s.size() > 0)
	{
		toLower(s);
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));

		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}
}

bool Utils::toCompare(std::string& a, std::string b)
{
	toLowerAndTrim(a);
	toLower(b);
	return a == b;
}

std::string Utils::GetColor(Colors col)
{
	return "\033[" + std::to_string((int)col) + "m";
}
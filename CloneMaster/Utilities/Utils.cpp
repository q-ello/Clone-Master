#include "Utils.h"

#include <locale>
#include <map>
#include <algorithm> 
#include <cctype>

std::string Utils::toLower(const std::string& s)
{
	std::string lower = "";
	std::for_each(s.begin(), s.end(), [&lower](unsigned char ch) {
		lower += std::tolower(ch);
		});
	return lower;
}

void Utils::toLowerAndTrim(std::string& s)
{
	if (s.size() > 0)
	{
		s = toLower(s);
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
	std::string lowB = toLower(b);
	std::string delimeter = " ";
	size_t pos = lowB.find(delimeter);
	if (pos != std::string::npos)
	{
		lowB = lowB.substr(pos);
	}
	return a == lowB;
}

std::string Utils::GetColor(Colors col)
{
	//TODO: rewrite that
	return "\033[" + std::to_string((int)col) + "m";
}
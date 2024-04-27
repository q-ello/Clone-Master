#pragma once

#include <map>

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	UP,
	DOWN
};

static std::map<std::string, Direction> DirectionsToEnum
{
	{"north", NORTH},
	{"east", EAST},
	{"south", SOUTH},
	{"west", WEST},
	{"up", UP},
	{"down", DOWN},
	{"n", NORTH},
	{"e", EAST},
	{"s", SOUTH},
	{"w", WEST},
	{"u", UP},
	{"d", DOWN},
};


static std::map<Direction, std::string> DirectionsToString
{
	{NORTH, "north"},
	{EAST, "east"},
	{SOUTH, "south"},
	{WEST, "west"},
	{UP, "up"},
	{DOWN, "down"},
};

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

static std::map<std::string, Direction> DirectionsMapped
{
	{"north", NORTH},
	{"east", EAST},
	{"south", SOUTH},
	{"west", WEST},
	{"up", UP},
	{"down", DOWN},
};

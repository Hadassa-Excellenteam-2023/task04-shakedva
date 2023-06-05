#pragma once
#include <iostream>

struct Coordinates
{
	double _x, _y;
	bool operator==(const Coordinates& other) const
	{
		return _x == other._x && _y == other._y;
	}
};

struct sortByX {
	bool operator()(const Coordinates& lhs, const Coordinates& rhs) const
	{
		return (lhs._x < rhs._x);
	}
};
struct sortByY {
	bool operator()(const Coordinates& lhs, const Coordinates& rhs) const
	{
		return (lhs._y < rhs._y);
	}
};

struct sortByXpair {
	bool operator()(const std::pair<const Coordinates, std::string>& lhs, const std::pair<const Coordinates, std::string>& rhs) const {
		return lhs.first._x < rhs.first._x;
	}
};

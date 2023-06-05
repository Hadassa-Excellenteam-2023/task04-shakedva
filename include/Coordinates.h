#pragma once
#include <iostream>
#include <math.h> 
#include <algorithm>
#include <unordered_map>

struct Coordinates
{
	double _x, _y;
	bool operator==(const Coordinates& other) const
	{
		return _x == other._x && _y == other._y;
	}
};

struct SortByX {
	bool operator()(const Coordinates& lhs, const Coordinates& rhs) const
	{
		return (lhs._x < rhs._x);
	}
};
struct SortByY {
	bool operator()(const Coordinates& lhs, const Coordinates& rhs) const
	{
		return (lhs._y < rhs._y);
	}
};

struct SortByXpair {
	bool operator()(const std::pair<const Coordinates, std::string>& lhs, const std::pair<const Coordinates, std::string>& rhs) const {
		return lhs.first._x < rhs.first._x;
	}
};

//todo change into class? 
struct Norm
{
	//typedef double (*NormFunctionPointer)();
	typedef double (Norm::*NormFunctionPointer)(const Coordinates&, const Coordinates&);

	std::unordered_map<int, NormFunctionPointer> _normFunctionMap;
	Norm()
	{
		_normFunctionMap[0] = &Norm::euclidean;
		_normFunctionMap[1] = &Norm::linfChebyshev;
		_normFunctionMap[2] = &Norm::manhattan;
	}

private:
	double euclidean(const Coordinates& coord0, const Coordinates& coord1)
	{
		double xDelta = coord0._x - coord1._x;
		double yDelta = coord0._y - coord1._y;
		return sqrt(pow(xDelta, 2) + pow(yDelta, 2));
	}

	double linfChebyshev(const Coordinates& coord0, const Coordinates& coord1)
	{
		double xDelta = abs(coord0._x - coord1._x);
		double yDelta = abs(coord0._y - coord1._y);
		return std::max(xDelta, yDelta);
	}

	double manhattan(const Coordinates& coord0, const Coordinates& coord1)
	{
		double xDelta = abs(coord0._x - coord1._x);
		double yDelta = abs(coord0._y - coord1._y);
		return xDelta + yDelta;
	}
};


//std::cout << "coord0:\t" << coord0._x << " " << coord0._y << std::endl;
//std::cout << "coord1:\t" << coord1._x << " " << coord1._y << std::endl;

//std::cout << "xDelta: " << xDelta << "yDelta: " << yDelta << std::endl;
//std::cout << sqrt(pow(xDelta, 2) + pow(yDelta, 2)) << std::endl;

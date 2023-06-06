#pragma once
#include <algorithm>
#include <unordered_map>
#include <math.h>
#include "Coordinates.h"

class Norm
{
public:
	typedef double (Norm::* NormFunctionPointer)(const Coordinates&, const Coordinates&);

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
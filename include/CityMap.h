#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "Coordinates.h"


class CityMap
{
public:
	CityMap();
	void parseMap();
	void findClosestCitiesByRadius(std::string, int, int);

private:
	void print();
	bool validateCityName(std::string);
	bool validateRadius(int);
	bool validateNorm(int);
	auto claculateBoundingSquare();
	std::pair<double, std::string> calculateDistance(const Coordinates&, const std::pair<Coordinates, std::string>&, Norm&, int);
	std::ifstream _mapFile;
	Norm _norm;

	std::multimap<Coordinates, std::string, SortByX> _coordinatesToCityLesserX;
	std::multimap<Coordinates, std::string, SortByY> _coordinatesToCityLesserY;
	std::map<std::string, Coordinates> _cityToCoordinates;
};

//todo north of the selected city
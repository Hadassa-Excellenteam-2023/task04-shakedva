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
	void findClosestCitiesByRadius(std::string, double);

private:
	void print();
	bool validateCityName(std::string);
	bool validateRadius(int);
	std::ifstream _mapFile;

	std::multimap<Coordinates, std::string, sortByX> _coordinatesToCityLesserX;
	std::multimap<Coordinates, std::string, sortByY> _coordinatesToCityLesserY;
	std::map<std::string, Coordinates> _cityToCoordinates;
};
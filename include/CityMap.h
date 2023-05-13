#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>

class CityMap
{
public:
	CityMap();
	void parseMap();
private:
	std::ifstream _mapFile;
	std::map<std::string, std::pair<double, double>> _cityToCoordinates;
	std::map<std::pair<double, double>, std::string> _coordinatesToCity;

};
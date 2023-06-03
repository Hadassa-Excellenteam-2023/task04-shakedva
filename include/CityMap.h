#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

class CityMap
{
public:
	CityMap();
	void parseMap();
	void filterByX();

private:
	void print();
	std::ifstream _mapFile;
	std::map<std::string, std::pair<double, double>> _cityToCoordinates;
	std::map<std::pair<double, double>, std::string> _coordinatesToCity;
	std::map<double, std::vector<double>> _xToY;
	std::map<double, std::vector<double>> _yToX;

};
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

struct sortByX {
	bool operator()(const std::pair<double, double>& l, const std::pair<double, double>& r) const
	{
		return (l.first < r.first);
	}
};
struct sortByY {
	bool operator()(const std::pair<double, double>& l, const std::pair<double, double>& r) const
	{
		return (l.second < r.second);
	}
};

class CityMap
{
public:
	CityMap();
	void parseMap();
	void findClosestCitiesByRadius(std::string, double);

private:
	void print();
	std::ifstream _mapFile;

	std::multimap<std::pair<double, double>, std::string, sortByX> _coordinatesToCityLesserX;
	std::multimap<std::pair<double, double>, std::string, sortByY> _coordinatesToCityLesserY;
	std::map<std::string, std::pair<double, double>> _cityToCoordinates;

	//std::map<std::pair<double, double>, std::string> _coordinatesToCity;
	//std::map<double, std::vector<double>> _xToY;
	//std::map<double, std::vector<double>> _yToX;

};
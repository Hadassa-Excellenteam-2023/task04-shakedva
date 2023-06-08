#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "Coordinates.h"
#include "Norm.h"


class CityMap
{
public:
	CityMap();
	~CityMap();
	void run();
	
private:
	void parseMap();
	void findClosestCitiesByRadius(std::string, double, int);
	bool validateCityName(std::string) const;
	bool validateRadius(double) const;
	bool validateNorm(int) const;
	std::multimap <Coordinates, std::string, SortByX> calculateBoundingSquare(const Coordinates&, double);
	std::multimap<double, std::string> mapDistanceToCity(auto, const Coordinates&, int);
	std::pair<double, std::string> calculateDistance(const Coordinates&, const std::pair<Coordinates, std::string>&, Norm&, int);
	std::vector<std::string> getCitiesInRadius(std::multimap<double, std::string>, int);
	size_t getNumOfNorthernCities(const Coordinates&, std::multimap<double, std::string>, int);
	
	void printInformation(const std::vector<std::string>&, size_t) const;
	
	std::ifstream _mapFile;
	Norm _norm;

	std::multimap<Coordinates, std::string, SortByX> _coordinatesToCityLesserX;
	std::multimap<Coordinates, std::string, SortByY> _coordinatesToCityLesserY;
	std::unordered_map<std::string, Coordinates> _cityToCoordinates;
};
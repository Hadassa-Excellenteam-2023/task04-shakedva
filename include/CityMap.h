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
	bool validateCityName(std::string);
	bool validateRadius(int);
	bool validateNorm(int);
	std::multimap <Coordinates, std::string, SortByX> calculateBoundingSquare(const Coordinates&, int);
	std::multimap<double, std::string> mapDistanceToCity(auto, const Coordinates&, int);
	std::pair<double, std::string> calculateDistance(const Coordinates&, const std::pair<Coordinates, std::string>&, Norm&, int);
	std::vector<std::string> getCitiesInRadius(std::multimap<double, std::string>, int);
	size_t getNumOfNorthernCities(const Coordinates&, std::multimap<double, std::string>, int);
	
	void printInformation(std::vector<std::string>, size_t);
	
	std::ifstream _mapFile;
	Norm _norm;

	std::multimap<Coordinates, std::string, SortByX> _coordinatesToCityLesserX;
	std::multimap<Coordinates, std::string, SortByY> _coordinatesToCityLesserY;
	std::map<std::string, Coordinates> _cityToCoordinates;
};
#include "CityMap.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>


//const std::string PATH = "data.txt";
const std::string PATH = "dataTest.txt";

CityMap::CityMap()
{
	_mapFile.open(PATH, std::ios::in);
	if (!_mapFile.is_open()) // file didn't open
	{
		//todo throw exception
		exit(EXIT_FAILURE);
	}
	parseMap();

	print();
}

void CityMap::parseMap()
{
	std::string line;
	int i = 0;
	while (std::getline(_mapFile, line))
	{
		std::string cityName = line;
		long double x, y;
		char sep;
		std::getline(_mapFile, line); // get the coordinates

		std::istringstream iss(line);
		
		iss  >> x >> sep >> y;
		std::pair coordinates = std::make_pair(x, y);
		
		_coordinatesToCityLesserX.insert(std::make_pair(coordinates, cityName));
		_coordinatesToCityLesserY.insert(std::make_pair(coordinates, cityName));
		_cityToCoordinates.insert(std::make_pair(cityName, coordinates));
	}

}

void CityMap::findClosestCitiesByRadius(std::string cityName, double radius)
{
	auto cityCoords = _cityToCoordinates.find(cityName);
	if (cityCoords == _cityToCoordinates.end())
	{
		std::cout << "not found\n";
		return ;
	}
	std::cout << "x: " << cityCoords->second.first << " y: " << cityCoords->second.second << std::endl;
	double cityX = cityCoords->second.first;
	double cityY = cityCoords->second.second;
	//auto xBeginIt = _coordinatesToCityLesserX.lower_bound(cityX - radius);
}

void CityMap::print()
{
	std::cout << "_cityToCoordinates\n";
	for (auto it = _cityToCoordinates.cbegin(); it != _cityToCoordinates.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "City: " << it->first << "\tx: " << it->second.first << "\ty: " << it->second.second << "\n";
	}
	std::cout << "-----------------------------------------\n";
	std::cout << "_coordinatesToCityLesserX\n";
	for (auto it = _coordinatesToCityLesserX.cbegin(); it != _coordinatesToCityLesserX.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "coordinates: x:" << it->first.first << "\ty: " << it->first.second << "\tcity: " << it->second << "\n";
	}
	std::cout << "-----------------------------------------\n";
	std::cout << "_coordinatesToCityLesserY\n";
	for (auto it = _coordinatesToCityLesserY.cbegin(); it != _coordinatesToCityLesserY.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "coordinates: x:" << it->first.first << "\ty: " << it->first.second << "\tcity: " << it->second << "\n";
	}
}

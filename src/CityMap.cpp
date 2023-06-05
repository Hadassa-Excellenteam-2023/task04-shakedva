#include "CityMap.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>

//const std::string PATH = "data.txt"; todo
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
		double x, y;
		char sep;
		std::getline(_mapFile, line); // get the coordinates

		std::istringstream iss(line);
		
		iss  >> x >> sep >> y;
		Coordinates coordinates = { x, y };
		_coordinatesToCityLesserX.insert(std::make_pair(coordinates, cityName));
		_coordinatesToCityLesserY.insert(std::make_pair(coordinates, cityName));
		_cityToCoordinates.insert(std::make_pair(cityName, coordinates));
	}

}

void CityMap::findClosestCitiesByRadius(std::string cityName, double radius) //todo receive norm num
{

	//todo
	//validate name, raduis and norm 
	//calc intersection sequre
	
	if (!validateCityName(cityName) || !validateRadius(radius))
	{
		//todo throw exception
		std::cout << "invalid inputs\n";
		return;
	}

	auto cityCoords = _cityToCoordinates.find(cityName);
	double cityX = cityCoords->second._x;
	double cityY = cityCoords->second._y;

	auto xBeginIt = _coordinatesToCityLesserX.lower_bound({cityX - radius, 0});
	auto xEndIt = _coordinatesToCityLesserX.upper_bound({cityX + radius , 0});
	auto yBeginIt = _coordinatesToCityLesserY.lower_bound({0, cityY - radius});
	auto yEndIt = _coordinatesToCityLesserY.upper_bound({0, cityY + radius});

	std::multimap <Coordinates, std::string, sortByX > yRectangle(yBeginIt, yEndIt);
	std::multimap <Coordinates, std::string, sortByX > square;

	std::set_intersection(
		xBeginIt, xEndIt, 
		yRectangle.begin(), yRectangle.end(),
		std::inserter(square, square.begin()),
		sortByXpair()
	);

	int x = 1;

}

void CityMap::print()
{
	std::cout << "_cityToCoordinates\n";
	for (auto it = _cityToCoordinates.cbegin(); it != _cityToCoordinates.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "City: " << it->first << "\tx: " << it->second._x << "\ty: " << it->second._y << "\n";
	}
	std::cout << "-----------------------------------------\n";
	std::cout << "_coordinatesToCityLesserX\n";
	for (auto it = _coordinatesToCityLesserX.cbegin(); it != _coordinatesToCityLesserX.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "x:" << it->first._x << "\ty: " << it->first._y << "\tcity: " << it->second << "\n";
	}
	std::cout << "-----------------------------------------\n";
	std::cout << "_coordinatesToCityLesserY\n";
	for (auto it = _coordinatesToCityLesserY.cbegin(); it != _coordinatesToCityLesserY.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "x:" << it->first._x << "\ty: " << it->first._y << "\tcity: " << it->second << "\n";
	}
}

bool CityMap::validateCityName(std::string cityName)
{
	return _cityToCoordinates.find(cityName) != _cityToCoordinates.end();
}

bool CityMap::validateRadius(int radius)
{
	return radius > 0;
}

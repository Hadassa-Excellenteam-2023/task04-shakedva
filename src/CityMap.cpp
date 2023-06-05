#include "CityMap.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <functional>
#include <format>

//const std::string PATH = "data.txt"; todo
const std::string PATH = "dataTest.txt";
const std::string SEARCH_INFO = "Search result:\n{} city/cities found in the given radius.\n{} cities are to the north of the selected city.\nCity list:\n{}";

CityMap::CityMap()
{
	_mapFile.open(PATH, std::ios::in);
	if (!_mapFile.is_open()) // file didn't open
	{
		//todo throw exception
		exit(EXIT_FAILURE);
	}
	parseMap();
	// print(); todo delete
}

void CityMap::parseMap()
{
	std::string line;
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

void CityMap::findClosestCitiesByRadius(std::string cityName, int radius, int normIndex)
{
	//todo
	//validate name, raduis and norm throw exception
	
	if (!validateCityName(cityName) || !validateRadius(radius) || !validateNorm(normIndex))
	{
		//todo throw exception
		std::cout << "invalid inputs\n";
		return;
	}
	Coordinates currentCityCoords = _cityToCoordinates.find(cityName)->second;
	std::multimap <Coordinates, std::string, SortByX> square = calculateBoundingSquare(currentCityCoords, radius);
	std::multimap<double, std::string> distance = mapDistanceToCity(square, currentCityCoords, normIndex);

	std::cout << "-----------------------------------------\nBounding square";
	for (auto it = distance.cbegin(); it != distance.cend(); ++it)
	{
		std::cout <<it->first << " " << it->second << std::endl;
	}
	std::cout << "-----------------------------------------\n";
	std::cout << "inside radius\n";


	auto citiesUpToRadius = distance.upper_bound(radius);
	for (auto it = distance.cbegin(); it != citiesUpToRadius; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

	//calc northern cities
	std::multimap<double, std::string> northernCities;

	std::copy_if(
		distance.begin(), citiesUpToRadius,
		std::inserter(northernCities, northernCities.end()),
		[this, &currentCityCoords](const std::pair<double, std::string>& pair) {
			Coordinates coord = _cityToCoordinates[pair.second];
			return coord._x < currentCityCoords._x;
		}
	);

	std::cout << "northern cities size: " << northernCities.size();

}

std::pair<double, std::string> CityMap::calculateDistance(const Coordinates& currentCity,
	const std::pair<Coordinates, std::string>& squareCity, Norm& norm, int index) 
{
	double distance = (norm.*(norm._normFunctionMap[index]))(currentCity, squareCity.first);
	return std::make_pair(distance, squareCity.second);
}


std::multimap <Coordinates, std::string, SortByX> CityMap::calculateBoundingSquare(Coordinates cityCoords, int radius)
{
	double cityX = cityCoords._x;
	double cityY = cityCoords._y;

	auto xBeginIt = _coordinatesToCityLesserX.lower_bound({ cityX - radius, 0 });
	auto xEndIt = _coordinatesToCityLesserX.upper_bound({ cityX + radius , 0 });
	auto yBeginIt = _coordinatesToCityLesserY.lower_bound({ 0, cityY - radius });
	auto yEndIt = _coordinatesToCityLesserY.upper_bound({ 0, cityY + radius });

	std::multimap <Coordinates, std::string, SortByX> yRectangle(yBeginIt, yEndIt);
	std::multimap <Coordinates, std::string, SortByX> square;

	std::set_intersection(
		xBeginIt, xEndIt,
		yRectangle.begin(), yRectangle.end(),
		std::inserter(square, square.begin()),
		SortByXpair()
	);
	return square;
}

std::multimap<double, std::string> CityMap::mapDistanceToCity(auto square, Coordinates currentCityCoords, int normIndex)
{
	std::multimap<double, std::string> distance;

	std::transform(
		square.begin(), square.end(),
		std::inserter(distance, distance.begin()),
		[this, &currentCityCoords, normIndex](const std::pair<Coordinates, std::string>& squareCity)
		{
			return calculateDistance(currentCityCoords, squareCity, _norm, normIndex);
		});
	return distance;
}

bool CityMap::validateCityName(std::string cityName)
{
	return _cityToCoordinates.find(cityName) != _cityToCoordinates.end();
}

bool CityMap::validateRadius(int radius)
{
	return radius > 0;
}

bool CityMap::validateNorm(int norm)
{
	return norm >=0 && norm < 3;
}


void CityMap::printInformation(size_t numOfCitiesFound)
{
	//std::cout << std::endl << std::format(SEARCH_INFO, numOfCitiesFound, 0, "Adamsville, AL") << std::endl;
}

//todo delete
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
		std::cout << std::setprecision(8) << "x: (" << it->first._x << " " << it->first._y << "\t)city: " << it->second << "\n";
	}
	std::cout << "-----------------------------------------\n";
	std::cout << "_coordinatesToCityLesserY\n";
	for (auto it = _coordinatesToCityLesserY.cbegin(); it != _coordinatesToCityLesserY.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "x: (" << it->first._x << " " << it->first._y << "\t) city: " << it->second << "\n";
	}

	std::cout << "-----------------------------------------\n";

	for (auto it = _coordinatesToCityLesserX.cbegin(); it != _coordinatesToCityLesserX.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "(" << it->first._x << " ," << it->first._y << "\t)" << it->second << "\n";
	}
}


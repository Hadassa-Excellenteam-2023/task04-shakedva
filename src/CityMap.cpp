#include "CityMap.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <functional>
#include <format>
#include <vector>


//const std::string PATH = "data.txt"; todo
const std::string PATH = "dataTest.txt";
const std::string SEARCH_INFO = "Search result:\n{} city/cities found in the given radius.\n{} cities are to the north of the selected city.\nCity list:";
const std::string CITY_NAME_INPUT = "Please enter selected city name (with line break after it):";
const std::string RADIUS_INPUT = "Please enter the wanted radius:";
const std::string NORM_INPUT = "Please enter the wanted norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance): ";
const std::string EXIT_PROG = "0";
const std::string RADIUS_ERR = "The radius must be a positive number.";
const std::string NORM_ERR = "Invalid norm. Must be an integer in range 0 - 2.";
const std::string CITY_NAME_ERR = "The city '{}' does not exist.";

CityMap::CityMap()
{
	_mapFile.open(PATH, std::ios::in);
	if (!_mapFile.is_open()) // file didn't open
	{
		//todo throw exception
		exit(EXIT_FAILURE);
	}
	parseMap();
}

void CityMap::run()
{
	std::string cityName;
	double radius;
	int normIndex;

	std::cout << CITY_NAME_INPUT << std::endl;
	std::getline(std::cin, cityName);
	while (cityName != EXIT_PROG)
	{
		while (!validateCityName(cityName))
		{
			if (cityName == EXIT_PROG) {
				std::cout << "Bye" << std::endl;
				return;
			}
			std::cerr << std::format(CITY_NAME_ERR, cityName) << std::endl;
			std::cout << CITY_NAME_INPUT << std::endl;
			std::cin.clear();
			std::getline(std::cin, cityName);
		}

		std::cout << RADIUS_INPUT << std::endl;;
		while (!(std::cin >> radius) || !validateRadius(radius))
		{
			std::cerr << RADIUS_ERR << std::endl;
			std::cout << RADIUS_INPUT << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << NORM_INPUT << std::endl;;
		while (!(std::cin >> normIndex) || !validateNorm(normIndex))
		{
			std::cerr << NORM_ERR << std::endl;
			std::cout << NORM_INPUT << std::endl;;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		findClosestCitiesByRadius(cityName, radius, normIndex);

		std::cout << CITY_NAME_INPUT << std::endl;
		std::getline(std::cin, cityName);
	}
	std::cout << "Bye" << std::endl;
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

void CityMap::findClosestCitiesByRadius(std::string cityName, double radius, int normIndex)
{
	Coordinates currentCityCoords = _cityToCoordinates.find(cityName)->second;
	std::multimap <Coordinates, std::string, SortByX> square = calculateBoundingSquare(currentCityCoords, radius);
	std::multimap<double, std::string> distance = mapDistanceToCity(square, currentCityCoords, normIndex);
	std::vector<std::string> citiesInRadius = getCitiesInRadius(distance, radius);
	printInformation(citiesInRadius, getNumOfNorthernCities(currentCityCoords, distance, radius));
}

std::pair<double, std::string> CityMap::calculateDistance(const Coordinates& currentCity,
	const std::pair<Coordinates, std::string>& squareCity, Norm& norm, int index) 
{
	double distance = (norm.*(norm._normFunctionMap[index]))(currentCity, squareCity.first);
	return std::make_pair(distance, squareCity.second);
}

std::vector<std::string> CityMap::getCitiesInRadius(std::multimap<double, std::string> distance, int radius)
{
	std::vector<std::string> citiesInRadius;
	if(distance.size() > 1)
	{ 
		std::transform(++distance.begin(), distance.upper_bound(radius),
			std::back_inserter(citiesInRadius),
			[](const std::pair<const double, std::string>& pair) {
				return pair.second;
			});
	}
	return citiesInRadius;
}

size_t CityMap::getNumOfNorthernCities(const Coordinates& currentCityCoords, std::multimap<double, std::string> distance, int radius)
{
	return std::count_if(
		distance.begin(), distance.upper_bound(radius),
		[this, &currentCityCoords](const std::pair<double, std::string>& pair) {
			Coordinates coord = _cityToCoordinates[pair.second];
			return coord._x < currentCityCoords._x;
		}
	);
}


std::multimap <Coordinates, std::string, SortByX> CityMap::calculateBoundingSquare(const Coordinates& cityCoords, double radius)
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

std::multimap<double, std::string> CityMap::mapDistanceToCity(auto square, const Coordinates& currentCityCoords, int normIndex)
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

bool CityMap::validateRadius(double radius)
{
	return radius > 0;
}

bool CityMap::validateNorm(int norm)
{
	return norm >=0 && norm < 3;
}
//
//bool CityMap::validateInputs(std::string cityName, int radius, int normIndex)
//{
//	bool valid = true;
//	if (!validateCityName(cityName))
//	{
//		std::cout << std::format(CITY_NAME_ERR, cityName) << std::endl;
//		valid = false;
//	}
//	if (!validateRadius(radius))
//	{
//		std::cout << RADIUS_ERR << std::endl;
//		valid = false;
//	}
//	if (!validateNorm(normIndex))
//	{
//		std::cout << NORM_ERR << std::endl;
//		valid = false;
//	}
//
//	return valid;
//}

void CityMap::printInformation(const std::vector<std::string>& citiesInRadius, size_t numOfNorthernCities) const
{
	std::cout << std::endl << std::format(SEARCH_INFO, citiesInRadius.size(), numOfNorthernCities) << std::endl;
	std::copy(citiesInRadius.begin(), citiesInRadius.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
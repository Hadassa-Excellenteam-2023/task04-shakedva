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

		_cityToCoordinates.insert(std::make_pair(cityName, coordinates));
		_coordinatesToCity.insert(std::make_pair(coordinates, cityName));
		_xToY[x].push_back(y);
		_yToX[y].push_back(x);

	}
	
	//print();
	filterByX();
}

void CityMap::filterByX()
{
//	std::map<double, std::vector<double>>mapX;
	std::map<double,std::vector< double>> filteredMap;

	double lowerBound = 30;
	double upperBound = 32; // inclusive

	//  filter the map 
	std::copy_if(_xToY.begin(), _xToY.end(), std::inserter(filteredMap, filteredMap.begin()),
		[lowerBound, upperBound](const std::pair<int, std::vector< double>>& pair) {
			return pair.first >= lowerBound && pair.first <= upperBound;
		});

	// print the filtered map
	for (auto it = filteredMap.cbegin(); it != filteredMap.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "x: " << it->first << " y: ";// << it->second << "\n";
		for (const auto& value : filteredMap[it->first]) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

}

void CityMap::print()
{
	std::cout << "_cityToCoordinates\n";
	for (auto it = _cityToCoordinates.cbegin(); it != _cityToCoordinates.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "City: " << it->first << " x: " << it->second.first << " y: " << it->second.second << "\n";
	}

	std::cout << "_coordinatesToCity\n";
	for (auto it = _coordinatesToCity.cbegin(); it != _coordinatesToCity.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "x: " << it->first.first << " y: " << it->first.second << " City: " << it->second << "\n";
	}

	std::cout << "_xToY\n";
	for (auto it = _xToY.cbegin(); it != _xToY.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "x: " << it->first << " y: ";
		for (const auto& value : _xToY[it->first]) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "_yToX\n";
	for (auto it = _yToX.cbegin(); it != _yToX.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "y: " << it->first << " x: ";
		for (const auto& value : _yToX[it->first]) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}

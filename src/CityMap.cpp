#include "CityMap.h"
#include <sstream>
#include <iomanip>


const std::string PATH = "data.txt";

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
//		_cityToCoordinates[cityName] = coordinates;

		_cityToCoordinates.insert(std::make_pair(cityName, coordinates));
		_coordinatesToCity.insert(std::make_pair(coordinates, cityName));

		i++;
		if (i == 10)
			break;
	}
	std::cout << "_cityToCoordinates\n";
	for (auto  it = _cityToCoordinates.cbegin(); it != _cityToCoordinates.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "City: " << it->first << " x: " << it->second.first << " y: " << it->second.second << "\n";
	}

	std::cout << "_coordinatesToCity\n";
	for (auto it = _coordinatesToCity.cbegin(); it != _coordinatesToCity.cend(); ++it)
	{
		std::cout << std::setprecision(8) << "x: " << it->first.first << " y: " << it->first.second << " City: " << it->second << "\n";
	}


}

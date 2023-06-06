#include "CityMap.h"
int main()
{
	//todo try except
	
	CityMap cm;
	std::string cityName;
	int radius;
	int normIndex;
	//std::cout << "Please enter selected city name (with line break after it):" << std::endl;
	//std::getline(std::cin, cityName);
	//std::cout << "Please enter the wanted radius:" << std::endl;;
	//std::cin >> radius;
	//std::cout << "Please enter the wanted norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance): " << std::endl;;
	//std::cin >> normIndex;
	//cm.findClosestCitiesByRadius(cityName, radius, normIndex);

	cm.findClosestCitiesByRadius("Akron, AL", 2, 0);
	cm.findClosestCitiesByRadius("Albertville, AL", 2, 0);
	//cm.findClosestCitiesByRadius("Akron, AL", 2, 1);
	//cm.findClosestCitiesByRadius("Akron, AL", 2, 2);
	//cm.findClosestCitiesByRadius("Eilat", 10);
	//cm.findClosestCitiesByRadius("Akron, AL", -2);


	return 0;
}
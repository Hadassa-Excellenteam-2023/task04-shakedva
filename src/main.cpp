#include "CityMap.h"
int main()
{
	//todo try except
	
	CityMap cm;
	std::string cityName;
	double radius;
	
	//std::cout << "Please enter selected city name (with line break after it):" << std::endl;
	//std::getline(std::cin, cityName);
	//std::cout << "Please enter the wanted radius:" << std::endl;;
	//std::cin >> radius;
	//cm.findClosestCitiesByRadius(cityName, radius);

	cm.findClosestCitiesByRadius("Akron, AL", 2, 0);
	cm.findClosestCitiesByRadius("Akron, AL", 2, 1);
	cm.findClosestCitiesByRadius("Akron, AL", 2, 2);
	
	//cm.findClosestCitiesByRadius("Eilat", 10);
	//cm.findClosestCitiesByRadius("Akron, AL", -2);


	return 0;
}
#include "CityMap.h"
int main()
{
	try {
		CityMap cm;
		cm.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
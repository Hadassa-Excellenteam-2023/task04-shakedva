# task04-shakedva 

## Data Structures

1. std::multimap<Coordinates, std::string, SortByX> -  multimap that maps between coordinate (x, y) to city name.  
The multimap is sorted by x values in an ascending order.
2. std::multimap<Coordinates, std::string, SortByY> - multimap that maps between coordinate (x, y) to city name.  
The multimap is sorted by y values in an ascending order.
3. std::unordered_map<std::string, Coordinates> - maps between city name to its coordinate (x, y).
At first I usd std::map, but as I wrote the readme I realized unordered map can be much more efficent due to it faster lookup.
4. std::unordered_map<int, NormFunctionPointer> - maps between integer to a norm function pointer.  
The function pointer can point to Euclidean distance, Linf Cebyshev distance and Manhattan distance.  
5. Coordinates is a struct used to represent two points x and y on the map.
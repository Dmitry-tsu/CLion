#include <algorithm>
#include <iostream>
#include <random>
#include <limits>
#include <set>
#include <vector>

typedef size_t TownIndex;
typedef std::vector<TownIndex> PathValue;
typedef int Distance;
typedef std::vector<Distance> DistanceRow;
typedef std::vector<DistanceRow> DistanceMatrix;
typedef std::set<TownIndex> TownSet;
class TravelingSalesman
 {
    DistanceMatrix distanceMatrix;
    PathValue currentPath;
    Distance currentPathLength;
    PathValue shortestPath;
    Distance shortestPathLength;
    TownSet unvisitedTowns;

    public:

 };

int main()
{

}
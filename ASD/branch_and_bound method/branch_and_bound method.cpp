#include <algorithm>
#include <iostream>
#include <random>
#include <limits>
#include <set>
#include <utility>
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
    void printDistanceMatrix()
    {
        std::cout << "\nDistance Matrix:\n";
        for (const auto& row : distanceMatrix)
        {
            for (const auto& distance : row) {
                std::cout << distance << "\t";
            }
            std::cout << "\n";
        }
    }

    TravelingSalesman(DistanceMatrix distances)
            : distanceMatrix(std::move(distances)), shortestPathLength(std::numeric_limits<Distance>::max())
    {

    }

    void findAndPrintShortestPath()
    {

    }

private:
    void printCurrentPath()
    {
        std::cout << "Current Path: ";
        for (auto townIndex : currentPath)
        {
            std::cout << townIndex + 1 << '\t';
        }
        std::cout << "Length: " << currentPathLength << std::endl;
    }

    void addTownWithDeltaDistance(TownIndex town, Distance deltaDistance = 0)
    {

    }

    void findShortestPath()
    {

    }

    bool tryToImproveCurrentPath()
    {

    }

    bool isPathComplete()
    {
        return currentPath.size() >= distanceMatrix.size() + 1;
    }

    bool tryToAddNextOptimalTown()
    {

    }

    bool tryToAddOptimalTown(TownIndex town)
    {

    }

    bool tryToAddNextOptimalUnvisitedTownNotLessThan(TownIndex townStart)
    {

    }

    bool tryBackingUpTown()
    {

    }

    TownIndex popAndGetCurrentTown()
    {

    }

    void printShortestPath()
    {
        std::cout << std::endl;
        for (auto townIndex : shortestPath)
        {
            std::cout << townIndex + 1 << '\t';
        }
        std::cout << std::endl;
    }

};

int main()
{
    std::ios::sync_with_stdio(false);
    int totalTowns{};

    do  {
        std::cout << "Total towns (>= 2): ";
        std::cin >> totalTowns;
    } while (totalTowns < 2);

    std::cout << "Enter distances between towns:" << std::endl;
    DistanceMatrix distances(totalTowns, DistanceRow(totalTowns));
    for (TownIndex from{}; from < TownIndex(totalTowns); ++from)
    {
        for (TownIndex to{}; to < TownIndex(totalTowns); ++to)
        {
            if (from == to)
            {
                continue;
            }
            std::cout << from + 1 << " - " << to + 1 << "\t: ";
            std::cin >> distances[from][to];
        }
    }
    TravelingSalesman salesman(distances);
    salesman.printDistanceMatrix();
}
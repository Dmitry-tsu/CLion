#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

typedef size_t                 TownIndex;
typedef std::vector<TownIndex> PathValue;
typedef int                    Distance;
typedef std::vector<Distance>  DistanceRow;
typedef std::vector<DistanceRow>  DistanceMatrix;
typedef std::set<TownIndex>    TownSet;
class TravelingSalesman
{
    DistanceMatrix      distanceMatrix;
    PathValue           currentPath;
    Distance            currentPathLength;
    PathValue           shortestPath;
    Distance            shortestPathLength;
    TownSet             unvisitedTowns;

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

    TravelingSalesman(const DistanceMatrix &distances)
            : distanceMatrix(distances), shortestPathLength(std::numeric_limits<Distance>::max())
    {
        for (TownIndex townIndex{}; townIndex < distances.size(); ++townIndex)
        {
            unvisitedTowns.insert(townIndex);
        }
        addTownWithDeltaDistance(0);
    }

    void findAndPrintShortestPath()
    {
        findShortestPath();
        printShortestPath();
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
        currentPath.emplace_back(town);
        unvisitedTowns.erase(town);
        currentPathLength += deltaDistance;
        printCurrentPath();
    }

    void findShortestPath()
    {
        do
        {
            if (tryToImproveCurrentPath())
            {
                shortestPath = currentPath;
                shortestPathLength = currentPathLength;
            }
        } while (tryBackingUpTown());
    }

    bool tryToImproveCurrentPath()
    {
        while (!isPathComplete() && tryToAddNextOptimalTown()) {}
        return isPathComplete();
    }

    bool isPathComplete()
    {
        return currentPath.size() >= distanceMatrix.size() + 1;
    }

    bool tryToAddNextOptimalTown()
    {
        return currentPath.size() == distanceMatrix.size()
               ? tryToAddOptimalTown(0)
               : tryToAddNextOptimalUnvisitedTownNotLessThan(0);
    }

    bool tryToAddOptimalTown(TownIndex town)
    {
        auto deltaDistance = distanceMatrix[currentPath.back()][town];
        bool result = currentPathLength + deltaDistance < shortestPathLength;
        if (result)
        {
            addTownWithDeltaDistance(town, deltaDistance);
        }
        return result;
    }

    bool tryToAddNextOptimalUnvisitedTownNotLessThan(TownIndex townStart)
    {
        return std::find_if(
                unvisitedTowns.lower_bound(townStart),
                unvisitedTowns.end(),
                [&](auto town) { return this->tryToAddOptimalTown(town); }) != unvisitedTowns.end();
    }

    bool tryBackingUpTown()
    {
        return currentPath.size() > 1 &&
               (tryToAddNextOptimalUnvisitedTownNotLessThan(popAndGetCurrentTown() + 1) ||
                tryBackingUpTown());
    }

    TownIndex popAndGetCurrentTown()
    {
        auto currentTown = currentPath.back();
        currentPath.pop_back();
        if (currentTown)
        {
            unvisitedTowns.insert(currentTown);
        }
        auto previousTown = currentPath.back();
        currentPathLength -= distanceMatrix[previousTown][currentTown];
        return currentTown;
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
    do {
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
    salesman.findAndPrintShortestPath();
}

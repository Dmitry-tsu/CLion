#include <algorithm>
#include <iostream>
#include <random>
#include <limits>
#include <set>
#include <vector>

typedef size_t                 Index;
typedef std::vector<Index>     Val;
typedef int                    Dist;
typedef std::vector<Dist>      Row;
typedef std::vector<Row>       Matrix;
typedef std::set<Index>        Towns;

class TravelingSalesman
{
    Matrix       distMatrix;
    Val          currPath;
    Dist         currPathLen{};
    Val          shortestPath;
    Dist         shortestPathLen;
    Towns        unvisitedTowns;

public:
    void printDistMatrix()
    {
        std::cout << "\nDistance Matrix:\n";
        for (const auto& row : distMatrix)
        {
            for (const auto& distance : row)
            {
                std::cout << distance << "\t";
            }
            std::cout << "\n";
        }
    }

    explicit TravelingSalesman(const Matrix &distances)
            : distMatrix(distances), shortestPathLen(std::numeric_limits<Dist>::max())
    {
        for (Index townIndex{}; townIndex < distances.size(); ++townIndex)
        {
            unvisitedTowns.insert(townIndex);
        }
        addTown(0);
    }

    void findPrintShortestPath()
    {
        findShortestPath();
        printShortestPath();
    }

private:
    void printCurrPath()
    {
        std::cout << "Current Path: ";
        for (auto townIndex : currPath)
        {
            std::cout << townIndex + 1 << '\t';
        }
        std::cout << "Length: " << currPathLen << std::endl;
    }

    void addTown(Index town, Dist deltaDist = 0)
    {
        currPath.emplace_back(town);
        unvisitedTowns.erase(town);
        currPathLen += deltaDist;
        printCurrPath();
    }

    void findShortestPath()
    {
        do
        {
            if (improveCurrPath())
            {
                shortestPath = currPath;
                shortestPathLen = currPathLen;
            }
        } while (tryBackingUpTown());
    }

    bool improveCurrPath()
    {
        while (!isPathComplete() && addNextOptimalTown()) {}
        return isPathComplete();
    }

    bool isPathComplete()
    {
        return currPath.size() >= distMatrix.size() + 1;
    }

    bool addNextOptimalTown()
    {
        return currPath.size() == distMatrix.size()
               ? addOptimalTown(0)
               : addNextOptimalUnvisitedTownNotLessThan(0);
    }

    bool addOptimalTown(Index town)
    {
        auto deltaDist = distMatrix[currPath.back()][town];
        bool result = currPathLen + deltaDist < shortestPathLen;
        if (result) {
            addTown(town, deltaDist);
        }
        return result;
    }

    bool addNextOptimalUnvisitedTownNotLessThan(Index townStart)
    {
        return std::find_if(
                unvisitedTowns.lower_bound(townStart),
                unvisitedTowns.end(),
                [&](auto town) { return this->addOptimalTown(town); }) != unvisitedTowns.end();
    }

    bool tryBackingUpTown()
    {
        while (currPath.size() > 1)
        {
            if (addNextOptimalUnvisitedTownNotLessThan(popAndGetCurrentTown() + 1))
            {
                return true;
            }
        }
        return false;
    }

    Index popAndGetCurrentTown()
    {
        auto currentTown = currPath.back();
        currPath.pop_back();
        if (currentTown)
        {
            unvisitedTowns.insert(currentTown);
        }
        auto previousTown = currPath.back();
        currPathLen -= distMatrix[previousTown][currentTown];
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

    int lowerLimit, upperLimit;
    std::cout << "Enter lower and upper limits for random distances: ";
    std::cin >> lowerLimit >> upperLimit;

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(lowerLimit, upperLimit);

    Matrix distances(totalTowns, Row(totalTowns));
    for (Index from{}; from < Index(totalTowns); ++from)
    {
        for (Index to{}; to < Index(totalTowns); ++to)
        {
            if (from == to)
            {
                distances[from][to] = 0;
            }
            else
            {
                distances[from][to] = distribution(generator);
            }
        }
    }

    TravelingSalesman salesman(distances);
    salesman.printDistMatrix();
    salesman.findPrintShortestPath();
}

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>



void generateRandomArray(std::vector<int>& arr, int minValue, int maxValue)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minValue, maxValue);

    for (int& num : arr)
    {
        num = dis(gen);
    }
}


void writeArrayToFile(const std::vector<int>& arr, const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        for (int num : arr)
        {
            file << num << std::endl;
        }
        file.close();
        std::cout << "Array has been written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

void shellSortHibbard(std::vector<int>& arr)
{
    int n = arr.size();
    int gap = 1;
    while (gap < n) {
        gap = 2 * gap + 1;
    }
    gap = (gap - 1) / 2;

    while (gap > 0) {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
        gap = (gap - 1) / 2;
    }
}

void shellSortPratt(std::vector<int>& arr)
{
    int n = arr.size();
    std::vector<int> gaps;
    int gap = 1;
    while (gap <= n) {
        gaps.push_back(gap);
        gap = 3 * gap + 1;
    }

    for (int k = gaps.size() - 1; k >= 0; k--) {
        gap = gaps[k];
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shellSortSedgewick(std::vector<int>& arr)
{
    int n = arr.size();
    std::vector<int> gaps;
    int k = 1;
    int gap = 1;
    while (gap < n)
    {
        gaps.push_back(gap);
        gap = (1 << k) * (1 << k + 1) - (1 << k) + 1;
        k++;
    }

    for (int i = gaps.size() - 1; i >= 0; i--)
    {
        gap = gaps[i];
        for (int j = gap; j < n; j++)
        {
            int temp = arr[j];
            int k = j;
            while (k >= gap && arr[k - gap] > temp)
            {
                arr[k] = arr[k - gap];
                k -= gap;
            }
            arr[k] = temp;
        }
    }
}

bool isSorted(const std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}

double measureShellSort(const std::vector<int>& arr, void (*shellSort)(std::vector<int>&))
{
    std::vector<int> temp = arr;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    shellSort(temp);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - start;

    return diff.count();
}

int main()
{
    const std::vector<int> sizes = {10000, 100000, 1000000};
    const std::vector<std::pair<int, int>> ranges = {{-10, 10}, {-1000, 1000}, {-100000, 100000}};
    // std::pair является контейнером стандартной библиотеки C++, который позволяет хранить пару значений разных типов
    for (int size : sizes)
    {
        for (const auto& range : ranges)
        {
            std::vector<int> arr(size);
            generateRandomArray(arr, range.first, range.second);

            std::string filename = "array_" + std::to_string(size) + "_" +
                                   std::to_string(range.first) + "_" + std::to_string(range.second) + ".txt";
            writeArrayToFile(arr, filename);


            std::vector<int> temp = arr;
            shellSortHibbard(temp);
            if (isSorted(temp))
            {
                std::cout << "Array in " << filename << " is sorted with Hibbard's Shell Sort" << std::endl;
            }
            else
            {
                std::cerr << "Array in " << filename << " is not sorted with Hibbard's Shell Sort" << std::endl;

            }
            double hibbardTime = measureShellSort(arr, shellSortHibbard);
            std::cout << "Time taken for Hibbard's Shell Sort in " << filename << ": "
                      << hibbardTime << " seconds\n" << std::endl;
            std::vector<int> temp2 = arr;
            shellSortPratt(temp2);
            if (isSorted(temp2))
            {
                std::cout << "Array in " << filename << " is sorted with Pratt's Shell Sort" << std::endl;
            }
            else
            {
                std::cerr << "Array in " << filename << " is not sorted with Pratt's Shell Sort" << std::endl;

            }
            double prattTime = measureShellSort(arr, shellSortPratt);
            std::cout << "Time taken for Pratt's Shell Sort in " << filename << ": "
                      << prattTime << " seconds\n" << std::endl;



            std::vector<int> temp3 = arr;
            shellSortSedgewick(temp3);
            if (isSorted(temp3))
            {
                std::cout << "Array in " << filename << " is sorted with Sedgewick's Shell Sort" << std::endl;
            }
            else
            {
                std::cerr << "Array in " << filename << " is not sorted with Sedgewick's Shell Sort" << std::endl;

            }
            double sedgewickTime = measureShellSort(arr, shellSortSedgewick);
            std::cout << "Time taken for Sedgewick's Shell Sort in " << filename << ": "
                      << sedgewickTime << " seconds\n" << std::endl;
        }
        double hibbardAverageTime = 0.0;
        double prattAverageTime = 0.0;
        double sedgewickAverageTime = 0.0;

        for (const auto& range : ranges)
        {
            std::vector<int> arr(size);
            generateRandomArray(arr, range.first, range.second);

            hibbardAverageTime += measureShellSort(arr, shellSortHibbard);
            prattAverageTime += measureShellSort(arr, shellSortPratt);
            sedgewickAverageTime += measureShellSort(arr, shellSortSedgewick);
        }

        hibbardAverageTime /= ranges.size();
        prattAverageTime /= ranges.size();
        sedgewickAverageTime /= ranges.size();

        std::string sizeString = std::to_string(size);
        for (const auto& range : ranges)
        {
            std::string filename = "array_" + sizeString + "_" +
                                   std::to_string(range.first) + "_" + std::to_string(range.second) + ".txt";

            std::cout << "Average time for Hibbard's Shell Sort in " << filename << ": "
                      << hibbardAverageTime << " seconds" << std::endl;
            std::cout << "Average time for Pratt's Shell Sort in " << filename << ": "
                      << prattAverageTime << " seconds" << std::endl;
            std::cout << "Average time for Sedgewick's Shell Sort in " << filename << ": "
                      << sedgewickAverageTime << " seconds" << std::endl;

            std::cout << std::endl;
        }
    }

    return 0;
}

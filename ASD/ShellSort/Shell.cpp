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
    std::vector<int> arr(10);
    generateRandomArray(arr, 1, 100);
    writeArrayToFile(arr, "input.txt");

    std::cout << "Array before sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl << "\n";

    std::vector<int> temp1 = arr;
    shellSortHibbard(temp1);
    std::cout << "Sorted Array using Hibbard's Shell Sort: ";
    for (int num : temp1)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    if (isSorted(temp1))
    {
        std::cout << "Array is sorted" << std::endl;
    }
    else
    {
        std::cout << "Array is not sorted" << std::endl;
    }

    double hibbardTime = measureShellSort(arr, shellSortHibbard);
    std::cout << "Time taken for Hibbard's Shell Sort: " << hibbardTime << " seconds\n" << std::endl;

    std::vector<int> temp2 = arr;
    shellSortPratt(temp2);
    std::cout << "Sorted Array using Pratt's Shell Sort: ";
    for (int num : temp2)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    if (isSorted(temp2))
    {
        std::cout << "Array is sorted" << std::endl;
    }
    else
    {
        std::cout << "Array is not sorted" << std::endl;
    }

    double prattTime = measureShellSort(arr, shellSortPratt);
    std::cout << "Time taken for Pratt's Shell Sort: " << prattTime << " seconds" << std::endl;

    return 0;
}


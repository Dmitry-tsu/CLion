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

void HoarSort(std::vector<int>& vec, const int left, const int right)
{
    if (left >= right) return;

    int i = left, j = right, x = vec[(left + right) / 2];

    while (i <= j)
    {
        while (vec[i] < x)
            i++;

        while (vec[j] > x)
            j--;

        if (i <= j)
        {
            std::swap(vec[i], vec[j]);
            i++;
            j--;
        }
    }

    HoarSort(vec, left, j);
    HoarSort(vec, i, right);
}

int main()
{
    int size = 10;
    std::vector<int> arr(size);
    generateRandomArray(arr, 1, 100);

    std::cout << "Before sorting:" << std::endl;
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    HoarSort(arr, 0, size - 1);

    std::cout << "After sorting:" << std::endl;
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    if (isSorted(arr))
    {
        std::cout << "The array is sorted." << std::endl;
    } else {
        std::cout << "The array is not sorted." << std::endl;
    }

    return 0;
}

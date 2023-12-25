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

void RadixSort(std::vector<int>& arr, int left, int right, int k)
{
    if (left >= right || k < 0) return;

    int i = left, j = right;

    while (i <= j)
    {
        while (i <= j && ((arr[i] >> k) & 1) == 0)
            i++;

        while (i <= j && ((arr[j] >> k) & 1) == 1)
            j--;

        if (i < j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    RadixSort(arr, left, j, k - 1);
    RadixSort(arr, i, right, k - 1);
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

    RadixSort(arr, 0, size - 1, sizeof(int) * 8 - 1);


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

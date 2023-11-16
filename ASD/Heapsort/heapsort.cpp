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

void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void siftDown(int* arr, int size, int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != index)
    {
        Swap(arr[index], arr[largest]);
        siftDown(arr, size, largest);
    }
}

void heapSort(int* arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        siftDown(arr, size, i);
    }

    for (int i = size - 1; i >= 1; i--)
    {
        Swap(arr[0], arr[i]);
        siftDown(arr, i, 0);
    }
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

    heapSort(arr.data(), size);

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


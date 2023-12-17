#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

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

void readArrayFromFile(std::vector<int>& arr, const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        int num;
        while (file >> num)
        {
            arr.push_back(num);
        }
        file.close();
        std::cout << "Array has been read from " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}
int main()
{
    const std::vector<std::string> filenames = {
            "array_10000_-10_10.txt",
            "array_10000_-1000_1000.txt",
            "array_10000_-100000_100000.txt",
            "array_100000_-10_10.txt",
            "array_100000_-1000_1000.txt",
            "array_100000_-100000_100000.txt",
            "array_1000000_-10_10.txt",
            "array_1000000_-1000_1000.txt",
            "array_1000000_-100000_100000.txt"
    };

    std::vector<double> averageSortingTimes(filenames.size(), 0);

    for (int i = 0; i < filenames.size(); i++)
    {
        std::vector<int> arr;
        readArrayFromFile(arr, filenames[i]);
        std::vector<int> temp = arr;

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        heapSort(temp.data(), temp.size());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = end - start;
        double sortingTime = diff.count();
        averageSortingTimes[i] = sortingTime;

        if (isSorted(temp))
        {
            std::cout << "The array in " << filenames[i] << " is sorted." << std::endl;
        }
        else
        {
            std::cerr << "The array in " << filenames[i] << " is not sorted." << std::endl;
        }
    }

    for (int i = 0; i < filenames.size(); i++)
    {
        std::cout << "Average sorting time for " << filenames[i] << ": " << averageSortingTimes[i] << " seconds" << std::endl;
    }

    return 0;
}



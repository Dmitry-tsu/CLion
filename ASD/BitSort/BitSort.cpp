#include <iostream>
#include <fstream>
#include <vector>
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

int FindMax(std::vector<int>& arr)
{
    int max = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void BitwiseSort(std::vector<int>& arr, int left_lim, int right_lim, int k)
{
    if (left_lim >= right_lim || k < 0)
        return;
    int i = left_lim, j = right_lim;
    int mask = 1 << k;
    while (i <= j)
    {
        while (i <= j && (arr[i] & mask) == 0)
            i++;
        while (i <= j && (arr[j] & mask) != 0)
            j--;
        if (i < j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    BitwiseSort(arr, left_lim, j, k - 1);
    BitwiseSort(arr, i, right_lim, k - 1);
}

void BitSort(std::vector<int> &arr)
{
    int max = FindMax(arr);
    int k = 31;
    int mask = 1 << 30;
    while ((max & mask) == 0)
    {
        mask >>= 1;
        k--;
    }
    int i = 0, j = arr.size() - 1;
    while (i <= j)
    {
        while (i < arr.size() && arr[i] < 0)
            i++;
        while (j >= 0 && arr[j] >= 0 )
            j--;
        if (i <= j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    BitwiseSort(arr, 0, j, k);
    BitwiseSort(arr, i, arr.size() - 1, k);
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

        std::vector<int> temp = arr;  // Делаем копию массива для проверки, отсортирован он или нет

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        BitSort(arr);  // Используем вашу функцию BitSort для сортировки массива
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::chrono::duration<double> diff = end - start;
        double sortingTime = diff.count();
        averageSortingTimes[i] = sortingTime;

        if (isSorted(arr))
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

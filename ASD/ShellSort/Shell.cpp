#include <iostream>
#include <fstream>
#include <vector>
#include <random>
// #include <chrono>


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
// Алгоритм Шелла с выбором длины промежутков по Хиббарду
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
// Проверка отсортированности массива
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
int main() {
    std::vector<int> arr(10); // Создаем вектор с размером 100
    generateRandomArray(arr, 1, 100); // Заполняем вектор случайными числами от 1 до 1000
    writeArrayToFile(arr, "input.txt"); // Записываем вектор в файл input.txt

    std::cout << "Array before sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    shellSortHibbard(arr); // Сортируем вектор с помощью алгоритма Шелла

    if (isSorted(arr)) { // Проверяем, отсортирован ли вектор
        std::cout << "Array is sorted" << std::endl;
        std::cout << "Sorted Array: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Array is not sorted" << std::endl;
    }

    return 0;
}


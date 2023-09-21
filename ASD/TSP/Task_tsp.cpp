#include <stdio.h>
#include <iostream>

// Функция для вывода матрицы на экран
void OutputMatrix(int** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%7d", matrix[i][j]);
        printf("\n");
    }
}

// Функция для вывода массива на экран
void PrintArray(int* array, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
}

// Функция для обмена значениями двух переменных
void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Функция для заполнения матрицы случайными числами
void RandomMatrix(int** matrix, int rows, int cols)
{
    srand(time(0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = rand() % 9 + 1;
}

// Функция для вычисления общего расстояния между городами
int CalculateTotalDistance(int* cities, int** matrix, int num_cities)
{
    int total_distance = 0;
    for (int i = 0; i < num_cities - 1; i++)
        total_distance += matrix[cities[i] - 1][cities[i + 1] - 1];

    total_distance += matrix[cities[num_cities - 1] - 1][cities[0] - 1];
    return total_distance;
}

// Функция для генерации следующей перестановки
bool NextPermutation(int n, int* array)
{
    int i = n - 2;
    while (i >= 0 && array[i] >= array[i + 1])
        i--;
    if (i < 0)
        return false;
    int j = n - 1;
    while (array[i] >= array[j])
        j--;

    Swap(array[i], array[j]);
    int k = i + 1;
    int l = n - 1;

    while (k < l)
    {
        Swap(array[k], array[l]);
        k++;
        l--;
    }
    return true;
}

// Функция для копирования значений из одного массива в другой
void CopyArray(int* source, int* destination, int size)
{
    for (int i = 0; i < size; i++)
        destination[i] = source[i];
}

// Функция для инициализации матрицы
void InitializeMatrix(int**& matrix, int num_cities)
{
    matrix = new int*[num_cities];
    for (int i = 0; i < num_cities; i++)
        matrix[i] = new int[num_cities];
}

// Функция для освобождения памяти, занимаемой матрицей
void DeleteMatrix(int**& matrix, int num_cities)
{
    for (int i = 0; i < num_cities; i++)
        delete[] matrix[i];
    delete[] matrix;
}

// Функция для поиска лучшего пути
void FindBestPath(int** matrix, int num_cities, int start_city)
{
    int path[num_cities + 1];
    path[0] = start_city;
    path[num_cities] = start_city;

    int n;
    for (int i = 1, n = 1; i < num_cities; n++)
    {
        if (n != start_city)
        {
            path[i] = n;
            i++;
        }
    }

    PrintArray(path, num_cities + 1);

    int min_distance = CalculateTotalDistance(path, matrix, num_cities - 1);
    std::cout << " " << min_distance << std::endl;

    int min_path[num_cities + 1];
    CopyArray(path, min_path, num_cities + 1);

    while (NextPermutation(num_cities, path))
    {
        PrintArray(path, num_cities + 1);
        int distance = CalculateTotalDistance(path, matrix, num_cities - 1);
        std::cout << " " << distance << std::endl;

        if (distance < min_distance)
        {
            min_distance = distance;
            CopyArray(path, min_path, num_cities + 1);
        }
    }

    std::cout << "Лучший путь: ";
    PrintArray(min_path, num_cities + 1);
    std::cout << " " << min_distance << std::endl;
}

void solveTSP()
{
    int** matrix;
    const int num_cities = 4;

    InitializeMatrix(matrix, num_cities);
    RandomMatrix(matrix, num_cities, num_cities);
    for (int i = 0; i < num_cities; i++)
        matrix[i][i] = 0;

    OutputMatrix(matrix, num_cities, num_cities);
    std::cout << std::endl;

    int start_city = 1;

    FindBestPath(matrix, num_cities, start_city);

    DeleteMatrix(matrix, num_cities);
}

int main()
{
    solveTSP();
    return 0;
}


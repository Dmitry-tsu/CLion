#include <iostream>
#include <chrono>

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
    srand(time(nullptr));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = rand() % 9 + 1;
}

// Функция для вычисления общего расстояния между городами
int CalculateTotalDistance(const int* cities, int** matrix, int num_cities)
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
void CopyArray(const int* source, int* destination, int size)
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
    std::cout << " Total weight: " << min_distance << std::endl;

    int min_path[num_cities + 1];
    CopyArray(path, min_path, num_cities + 1);

    while (NextPermutation(num_cities, path))
    {
        PrintArray(path, num_cities + 1);
        int distance = CalculateTotalDistance(path, matrix, num_cities - 1);
        std::cout << " Total weight: " << distance << std::endl;

        if (distance < min_distance)
        {
            min_distance = distance;
            CopyArray(path, min_path, num_cities + 1);
        }
    }

    std::cout << "BEST PATH: ";
    PrintArray(min_path, num_cities + 1);
    std::cout << " TOTAL WEIGHT: " << min_distance << std::endl;
}

// Функция для поиска худшего пути
void FindWorstPath(int** matrix, int num_cities, int start_city)
{
    int path[num_cities + 1];
    path[0] = start_city;
    path[num_cities] = start_city;
    for (int i = 1, n = 1; i < num_cities; n++)
    {
        if (n != start_city)
        {
            path[i] = n;
            i++;
        }
    }

    int min_distance = CalculateTotalDistance(path, matrix, num_cities - 1);
    int min_path[num_cities + 1];
    CopyArray(path, min_path, num_cities + 1);

    while (NextPermutation(num_cities, path))
    {
        int distance = CalculateTotalDistance(path, matrix, num_cities - 1);

        if (distance > min_distance)
        {
            min_distance = distance;
            CopyArray(path, min_path, num_cities + 1);
        }
    }

    std::cout << "WORST PATH: ";
    PrintArray(min_path, num_cities + 1);
    std::cout << " TOTAL WEIGHT: " << min_distance << std::endl;
}


// Функция, реализующая решение
/*void ExactSolveTSP()
{
    int** matrix;
    const int num_cities = 5;

    InitializeMatrix(matrix, num_cities);
    RandomMatrix(matrix, num_cities, num_cities);
    for (int i = 0; i < num_cities; i++)
        matrix[i][i] = 0;

    OutputMatrix(matrix, num_cities, num_cities);
    std::cout << std::endl;

    int start_city = 1;

    FindBestPath(matrix, num_cities, start_city);

    // FindWorstPath(matrix, num_cities, start_city);

    DeleteMatrix(matrix, num_cities);
}
*/
// Эвристика
// нахожд. мин. эл. в матрице
int MinimalElement(int** matr_way_weight, int number_city, int& i_min, int& j_min)
{
    int min_element = 1000; // Начальное значение для минимального элемента
    // Итерация по матрице для нахождения минимального элемента
    for (int i = 0; i < number_city; i++)
    {
        for (int j = 0; j < number_city; j++)
        {
            if (matr_way_weight[i][j] != 0 && matr_way_weight[i][j] < min_element)
            {
                min_element = matr_way_weight[i][j];
                i_min = i;
                j_min = j;
            }
        }
    }
    return min_element;
}
// Функция использ. для проверки наличия цикла в пути
bool SearchCycle(int* way, int number_city, int i, int j)
{
    int current_city = way[j];
    while (current_city != 0)
    {
        if (current_city == way[i])
            return true;
        current_city = way[2 * current_city - 1];
    }
    return false;
}
// функция для обновления матрицы
void TransformMatrix(int** matr_way_weight, int i_min, int j_min, int number_city)
{
    for (int i = 0; i < number_city; i++)
    {
        matr_way_weight[i][i_min] = 0;
        matr_way_weight[j_min][i] = 0;
    }
}
// собственно само решение

int Heuristics(int* way, int **matr_way_weight, int number_city,
               int &i_min, int &j_min, int min_element, int weight,
               int *heuristics_min_way, int starting_city)
{
    for (int i = 0, j = 1, k = 1;;)
    {
        min_element = MinimalElement(matr_way_weight, number_city, i_min, j_min);
        if (min_element == 1000)
            break;
        way[i] = i_min + 1;
        way[j] = j_min + 1;
        if (k != number_city)
        {
            if (SearchCycle(way, number_city, i, j))
            {
                way[i] = 0;
                way[j] = 0;
                matr_way_weight[i_min][j_min] = 0;
            }
            else
            {
                weight += min_element;
                TransformMatrix(matr_way_weight, i_min, j_min, number_city);
                i += 2;
                j += 2;
                k++;
            }
        }
        else
        {
            weight += min_element;
            TransformMatrix(matr_way_weight, i_min, j_min, number_city);
            i += 2;
            j += 2;
        }
    }
    int k = 0, i;
    for (int j = 0; j < number_city + 1; j++)
    {
        for (i = 0; way[i] != starting_city; i += 2);
        heuristics_min_way[k++] = way[i];
        starting_city = way[i + 1];
    }
    return weight;
}


/*
void HeuristicSolveTSP()
{
    int number_city = 5;  // количество городов
    // Инициализация матрицы путей и других переменных


    int** matr_way_weight; // инициализация матрицы путей
    ... как передать?

    int* way = new int[2 * number_city];
    int* heuristics_min_way = new int[number_city + 1];
    int i_min, j_min, min_element = 1000, weight = 0;
    int starting_city = 1; // указывает, с какого города начинается путь

    weight = Heuristics(way, matr_way_weight, number_city,
                        i_min, j_min, min_element, weight,
                        heuristics_min_way, starting_city);

    // Вывод результата
    std::cout << "BEST PATH (Heuristics): ";
    for (int i = 0; i < number_city; i++)
    {
        std::cout << heuristics_min_way[i] << " -> ";
    }
    std::cout << starting_city << std::endl;

    std::cout << "Total weight: " << weight << std::endl;

    // Освобождение памяти
    delete[] way;
    delete[] heuristics_min_way;
}
*/



int main()
{
    //ExactSolveTSP();
    //HeuristicSolveTSP();
    const int num_cities = 5;
    int** matrix;
    InitializeMatrix(matrix, num_cities);
    RandomMatrix(matrix, num_cities, num_cities);
    OutputMatrix(matrix, num_cities, num_cities);
    std::cout << std::endl;
    int start_city = 1;
    FindBestPath(matrix, num_cities, start_city);
    FindWorstPath(matrix, num_cities, start_city);
    DeleteMatrix(matrix, num_cities);
    // Эвристика
    return 0;
}


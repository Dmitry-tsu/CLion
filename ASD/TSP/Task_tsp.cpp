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

int Find_cols(int* a, int n, int D)
{
    for (int i = 1; i < n; i+=2)
        if (a[i] == D) return i;
    return -1;
}
//исключение строк и столбцов
bool Exceptions(int* arr, int n, int r, int c)
{
    int i;
    for (i = 0; i < n; i += 2)
        if (arr[i] == r || arr[i + 1] == c) return false;
    return true;
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
// решение

int Heuristics(int* way, int **matr_way_weight, int number_city, int &i_min, int &j_min, int min_element, int weight, int *heuristics_min_way, int starting_city)
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

float Percentag_Quality(int way_weight_h, int min_way_weight, int max_way_weight)
{
    float p; float a = way_weight_h - min_way_weight; float b = max_way_weight - min_way_weight;
    float d = a / b;
    return 100 - d * 100;
}

float Percentag_Speed(float time_h,float time)
{
    return  time / time_h * 100;

}

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    int** Matr_Way_Weight;
    int count_sity; // Number of cities
    int start_sity; // Starting city

    cout << "Number of cities: ";
    cin >> count_sity;

    cout << endl << "Starting city: ";
    cin >> start_sity;

    cout << endl;

    InitializeMatrix(Matr_Way_Weight, count_sity);
    RandomMatrix(Matr_Way_Weight, count_sity, count_sity);

    for (int i = 0; i < count_sity; i++)
    {
        Matr_Way_Weight[i][i] = 0;
    }

    auto start_exact = std::chrono::high_resolution_clock::now();
    FindBestPath(Matr_Way_Weight, count_sity, start_sity);
    auto end_exact = std::chrono::high_resolution_clock::now();
    float exact_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_exact - start_exact).count();

    auto start_worst = std::chrono::high_resolution_clock::now();
    FindWorstPath(Matr_Way_Weight, count_sity, start_sity);
    auto end_worst = std::chrono::high_resolution_clock::now();
    float worst_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_worst - start_worst).count();

    auto start_heuristic = std::chrono::high_resolution_clock::now();
    int* heuristic_path = new int[count_sity + 1];
    int heuristic_weight = Heuristics(heuristic_path, Matr_Way_Weight, count_sity, i_min, j_min, min_element, weight, heuristics_min_way, starting_city);
    auto end_heuristic = std::chrono::high_resolution_clock::now();
    float heuristic_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_heuristic - start_heuristic).count();

    cout << "The best path and its weight: ";
    PrintArray(Min_Way, count_sity + 1);
    cout << " " << min_way_weight << endl;

    cout << "The worst path and its weight: ";
    PrintArray(Max_Way, count_sity + 1);
    cout << " " << max_way_weight << endl;

    cout << "Heuristic decision; path and its weight: ";
    PrintArray(heuristic_path, count_sity + 1);
    cout << " " << heuristic_weight << endl;

    float quality_percentage = Percentag_Quality(heuristic_weight, min_way_weight, max_way_weight);
    float speed_percentage = Percentag_Speed(exact_time, heuristic_time);

    cout << "Quality percentage: " << quality_percentage << "%" << endl;
    cout << "Speed percentage: " << speed_percentage << "%" << endl;

    delete[] heuristic_path;
    DeleteMatrix(Matr_Way_Weight, count_sity);

    return 0;
}

#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>


void OutputMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << std::setw(7) << matrix[i][j];
        std::cout << std::endl;
    }
}


void RandomMatrix(int** matrix, int rows, int cols) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 20);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = dist(gen);
}



void OutputArray(int* array, int size) {
    for (int i = 0; i < size; i++)
        std::cout << array[i] << " ";
}



void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

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


void CopyArray(const int* source, int* destination, int size)
{
    for (int i = 0; i < size; i++)
        destination[i] = source[i];
}
int MinimalWay(int const* array, int** matrix, int n)
{
    int min = 0;
    int i;
    for (i = 0; i < n; i++)
        min += matrix[array[i] - 1][array[i + 1] - 1];

    min += matrix[array[i] - 1][array[0] - 1];
    return min;
}

int FindCols(int const* a, int n, int D)
{
    for (int i = 1; i < n; i+=2)
        if (a[i] == D) return i;
    return -1;
}
bool Exceptions(int const* array, int n, int r, int c)
{
    int i;
    for (i = 0; i < n; i += 2)
        if (array[i] == r || array[i + 1] == c) return false;
    return true;
}

bool FindCycle(int r, int c, int* arr, int n)
{
    int i,j;
    for (i = 0, j = 1; i < n; i += 2, j += 2)
        if (arr[i] == c && arr[j] == r) return false;
    i = FindCols(arr, n, r);
    while (i != -1)
    {
        if (arr[i - 1] == c) return false;
        i = FindCols(arr, n, arr[i - 1]);
    }
    return true;

}

void Dijkstra(int const count_city, int start_city, int** Matrix_Way_Weight, int* Min_Way, int* Max_Way, int& min_way_weight, int& max_way_weight) {
    int* Way = new int[count_city + 1];
    Way[0] = start_city;
    Way[count_city] = start_city;
    int i, n;
    for (i = 1, n = 1; i < count_city; n++)
        if (n != start_city) {
            Way[i] = n;
            i++;
        }
    min_way_weight = max_way_weight = MinimalWay(Way, Matrix_Way_Weight, count_city - 1);
    CopyArray(Way, Min_Way, count_city + 1);
    while (NextPermutation(count_city, Way)) {
        int way_weight = MinimalWay(Way, Matrix_Way_Weight, count_city - 1);
        if (way_weight < min_way_weight) {
            min_way_weight = way_weight;
            CopyArray(Way, Min_Way, count_city + 1);
        }
        if (way_weight > max_way_weight) {
            max_way_weight = way_weight;
            CopyArray(Way, Max_Way, count_city + 1);
        }
    }
    delete[] Way;
}


int Heuristics(int const count_city, int start_city, int** Matrix_Way_Weight, int *Min_Way_H)
{
    int min_weight;
    int* way_data = new int[2 * count_city];
    int n = 0, r, c;
    for (int i = 0; i < count_city * 2; i++) way_data[i] = 0;
    int row = 0, coll = 0;
    for (int i = 0; i < count_city; i++)
    {
        min_weight = 100;
        bool flag = true;
        for (r = 0; r < count_city; r++)
            for (c = 0; c < count_city; c++)
                if (r != c && Exceptions(way_data, n, r, c)  && Matrix_Way_Weight[r][c] < min_weight)
                {
                    if (i != count_city-1)  flag = FindCycle(r, c, way_data, n);
                    if (flag)
                    {
                        row = r; coll = c;
                        min_weight = Matrix_Way_Weight[r][c];
                    }
                }
        way_data[n] = row; way_data[n + 1] = coll;
        n += 2;
        OutputArray(way_data, count_city*2);
        std::cout << " " << min_weight << std::endl;
    }
    OutputArray(way_data, count_city * 2);
    int k = 0,i,j;

    for (j = 0; j < count_city+1; j++)
    {
        for (i = 0; way_data[i] != start_city; i += 2);

        Min_Way_H[k++] = way_data[i] + 1;
        start_city = way_data[i + 1];
    }
    int weight = MinimalWay(Min_Way_H, Matrix_Way_Weight, count_city - 1);
    delete[]way_data;
    return weight;
}
float Percentage_Quality(int way_weight_h, int min_way_weight, int max_way_weight)
{
    float a = way_weight_h - min_way_weight; float b = max_way_weight - min_way_weight;
    float d = a / b;
    return 100 - d * 100;
}

float Percentage_Speed(float time_h,float time)
{
    return  time / time_h * 100;

}
int main()
{
    using std::cout;
    using std::cin;
    using std::endl;
    int** Matrix_Way_Weight;
    int count_city;
    int start_city;
    cout << "Count of cities: ";
    cin >> count_city;
    cout <<endl<< "Starting city: ";
    cin >> start_city;
    cout << endl;
    int i, j;
    Matrix_Way_Weight = new int* [count_city];
    for (i = 0; i < count_city; i++)
        Matrix_Way_Weight[i] = new int[count_city];
    RandomMatrix(Matrix_Way_Weight, count_city, count_city);
    for (i = j = 0; i < count_city; i++, j++)
        Matrix_Way_Weight[i][j] = 0;
    OutputMatrix(Matrix_Way_Weight, count_city, count_city);
    cout << endl;

    int *Min_Way=new int [count_city + 1];
    int *Max_Way = new int[count_city + 1];
    int min_way_weight;
    int max_way_weight;

    auto start = std::chrono::high_resolution_clock::now();
    Dijkstra(count_city, start_city, Matrix_Way_Weight,Min_Way,Max_Way,min_way_weight,max_way_weight);
    auto end = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "The best path and its weight: ";
    OutputArray(Min_Way, count_city + 1);
    cout << " " << min_way_weight << endl;
    cout << "The worst path and its weight: ";
    OutputArray(Max_Way, count_city + 1);

    cout << " " << max_way_weight << endl << "Working hours: " << time <<" nanoseconds "<< endl;
    delete[]Min_Way;
    delete[]Max_Way;

    int* Min_Way_H = new int[count_city+1];
    start = std::chrono::high_resolution_clock::now();
    int way_weight_h=Heuristics(count_city, start_city-1, Matrix_Way_Weight, Min_Way_H);
    end = std::chrono::high_resolution_clock::now();
    float time_h = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Heuristic decision; path and its weight: ";
    OutputArray(Min_Way_H, count_city + 1);
    cout << " " << way_weight_h << endl <<"Working hours: " << time_h<<" nanoseconds " << endl;
    float perc_q = Percentage_Quality(way_weight_h, min_way_weight, max_way_weight);
    float perc_s = Percentage_Speed(time_h, time);
    cout << "Percentage of quality: "<<perc_q<<"%"<<endl<< "Percentage of speed: " << perc_s << "%" << endl;

    delete[]Min_Way_H;
    for (i = 0; i < count_city; i++)
        delete[]Matrix_Way_Weight[i];
    delete[]Matrix_Way_Weight;
    return 0;
}
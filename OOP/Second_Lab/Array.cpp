#include<iostream>
#include "Array.h"
#include"cassert"
template <typename T>

double calculateAvg(Array<T> arr)
{
    double avg = 0;
    if (arr.Size() == 0) return 0;

    for (int i = 0; i < arr.Size(); i++)
        avg += arr[i];
    avg /= arr.Size();
    return avg;
}

int main() {
    using std::cout;
    using std::cin;
    using std::endl;

    Array<int> arr_1(10, 0);
    Array<int> arr_2(10, 0);
    cout << "Creating an array of random numbers: ";
    arr_1.RandArray(0, 100);
    arr_1.Print();
    cout << "Creating an array of random numbers in increasing order: ";
    arr_1.RandArrayIns(-50, 100);
    arr_1.Print();
    cout << "Creating an array of random numbers in descending order: ";
    arr_1.RandArrayDes(-50, 100);
    arr_1.Print();
    cout << endl;

    return 0;
}




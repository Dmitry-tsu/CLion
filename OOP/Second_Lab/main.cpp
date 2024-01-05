#include <iostream>
#include "Array.h"

double calculateAvg(Array arr)
{
    double avg = 0;
    if (arr.size() == 0) return 0;

    for (int i = 0; i < arr.size(); i++)
        avg += arr[i];
    avg /= arr.size();
    return avg;
}
int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    Array arr_1(10, 0);
    Array arr_2(10,0);
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
    arr_2.RandArray(0, 100);
    cout << endl;

}

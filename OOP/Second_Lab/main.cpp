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

    Array arr(10, 0);
    cout << arr[3] << ' ' << arr[9] << endl;
    arr[3] = 4;
    arr[5] = arr[3];
    cout << calculateAvg(arr) << endl;
    arr.print();
    return 0;
}

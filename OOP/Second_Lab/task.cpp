#include"Array.h"
#include<iostream>

double calculateAvg(Array arr)
{
    double avg = 0;
    for (int i = 0; i < arr.size(); ++i)
    {
        avg += arr[i];
    }
    avg /= arr.size();
    return avg;
}

int main()
{
    Array arr(10, 0);

    std::cout << arr[3] << " " << arr[9] << std::endl;

    arr[3] = 3;
    arr[4] = arr[3];

    std::cout << "Average value: " << calculateAvg(arr) << std::endl;

    arr.Print();
}

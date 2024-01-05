#include "Fraction.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    int n, d;

    cout << "First fraction: Enter numerator and denominator: ";
    cin >> n >> d;

    while (d == 0)
    {
        cout << "Denominator can't be zero! Please enter a valid denominator: ";
        cin >> d;
    }
}






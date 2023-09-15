#include "Fraction.h"
#include <iostream>
using std::cout;
using std::endl;
int main()
{
    setlocale(0, "");
    Fraction a;
    Fraction b;
    Fraction c;
    a.print(); cout << endl;
    a.numerator = 5;
    a.denominator = 2;
    b.numerator = 6;
    b.denominator = 7;
    c = a.sum(b);
    c.print();
    cout <<"sum:\n" << endl;
    c = a.subtraction(b); c.print();
    cout<<"subtraction\n" << endl;
    c = a.multiplication(b); c.print();
    cout <<"multiplication\n" << endl;
    c = a.division(b); c.print();
    cout << "division\n" << endl;
}
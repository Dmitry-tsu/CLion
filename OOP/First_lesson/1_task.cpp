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

    Fraction f_1(n, d);
    cout << "f_1 = ";
    f_1.print();

    cout << "Second fraction: Enter numerator and denominator: ";
    cin >> n >> d;

    while (d == 0)
    {
        cout << "Denominator can't be zero! Please enter a valid denominator: ";
        cin >> d;
    }

    Fraction f_2(n, d);
    cout << "f_2 = ";
    f_2.print();

    cout << "Method set:" << endl;
    f_1.setNumerator(10);
    f_1.setDenominator(0);

    cout << "When we used the method set, the fraction f_1 = ";
    f_1.print();
    cout << endl;

    cout << "Method get:" << endl;
    int numerator_f_2 = f_2.getNumerator();
    int denominator_f_2 = f_2.getDenominator();

    cout << "When we used the method get, numerator of fraction f_2 = " << numerator_f_2
         << " and denominator of fraction f_2 = " << denominator_f_2 << endl;
    cout << endl;

    cout << "Default constructor:\nf_3 = ";
    Fraction f_3;
    f_3.print();
    cout << endl;

    cout << "Method summation: ";
    Fraction sum = f_1.summation(f_2);
    cout << "f_1 + f_2 = ";
    sum.print();

    cout << "Method subtraction: ";
    Fraction sub = f_1.subtraction(f_2);
    cout << "f_1 - f_2 = ";
    sub.print();

    cout << "Method multiplication: ";
    Fraction mul = f_1.multiplication(f_2);
    cout << "f_1 * f_2 = ";
    mul.print();

    cout << "Method division: ";
    Fraction div = f_1.division(f_2);
    cout << "f_1 / f_2 = ";
    div.print();
    cout << endl;

    cout << "Method reduce:\n";
    f_1.reduce();
    cout << "f_1 = ";
    f_1.print();

    f_2.reduce();
    cout << "f_2 = ";
    f_2.print();
    cout << endl;

    cout << "Methods comparison:\n";
    if (f_1 == f_2)
        cout << "Fractions are equal\n";
    else
        cout << "Fractions are not equal\n";

    if (f_1 != f_2)
        cout << "Fractions are not equal\n";
    else
        cout << "Fractions are equal\n";

    bool res = (f_1 < f_2);
    cout << "f_1 < f_2 ";

    if (res)
        cout << "True\n";
    else
        cout << "False\n";

    res = (f_1 > f_2);
    cout << "f_1 > f_2 ";

    if (res)
        cout << "True\n";
    else
        cout << "False\n";

    cout << endl;

    cout << "Methods sum, sub, mul, div with overload:\n";
    cout << "Method summation: ";
    sum = f_1 + f_2;
    cout << "f_1 + f_2 = ";
    sum.print();

    cout << "Method subtraction: ";
    sub = f_1 - f_2;
    cout << "f_1 - f_2 = ";
    sub.print();

    cout << "Method multiplication: ";
    mul = f_1 * f_2;
    cout << "f_1 * f_2 = ";
    mul.print();

    cout << "Method division: ";
    div = f_1 / f_2;
    cout << "f_1 / f_2 = ";
    div.print();
    cout << endl;

    cout << "Method input:\n";
    f_3.input();
    cout << "f_3 = ";
    f_3.print();
    cout << endl;

    //my methods
    cout << "Method representation of an integer as a fraction:\n";
    Fraction f_4;
    int a;
    cout << "Enter an integer: a = ";
    cin >> a;

    f_4.intToFraction(a);
    cout << "The number in fractional form: ";
    f_4.print();
    cout << endl;

    f_4.multiplyByInt(a);
    cout << "The numerator of a fraction multiplied by a given number ";
    f_4.print();
    cout << endl;

    cout << "Enter the degree of a number: a = ";
    cin >> a;
    cout << endl;
    cout << "Method exponentiation of fractions:\n";
    f_3.exponentiation(a);
    cout << "f_3^a = : ";
    f_3.print();

    cout << endl;
}






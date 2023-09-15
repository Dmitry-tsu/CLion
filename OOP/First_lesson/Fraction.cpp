#include "Fraction.h"
#include <iostream>
/*Fraction Fraction::sum(const Fraction a, const Fraction b)
{
	Fraction c;
	c.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
	c.denominator = a.denominator * b.denominator;
	return c;
}*/
Fraction::Fraction()
{
    numerator = 1;
    denominator = 1;
}
Fraction::Fraction(int numeratot,int denominator)
{
    numerator = numerator;
    denominator = denominator;
}
Fraction Fraction::sum(const Fraction b)
{
    Fraction c;
    c.numerator = numerator * b.denominator + b.numerator * denominator;
    c.denominator = denominator * b.denominator;
    return c;
}
Fraction Fraction::subtraction(const Fraction b)
{
    Fraction c;
    c.numerator = numerator * b.denominator - b.numerator * denominator;
    c.denominator = denominator * b.denominator;
    return c;
}
Fraction Fraction::multiplication(const Fraction b)
{
    Fraction c;
    c.numerator = numerator * b.numerator;
    c.denominator = denominator * b.denominator;
    return c;
}
Fraction Fraction::division(const Fraction b)
{
    Fraction c;
    c.numerator = numerator * b.denominator;
    c.denominator = denominator * b.numerator;
    return c;
}
void Fraction::print()
{
    printf("%d/%d", numerator, denominator);
}

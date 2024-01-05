#include "Fraction.h"
#include <iostream>
Fraction::Fraction(const int numerator, const int denominator) : m_numerator(numerator)
{
    if (denominator == 0)
    {
        std::cerr << "Fraction::Fraction: error: denominator is 0, result will be numerator/1.\n";
    }
    else
    {
        m_denominator = denominator;
    }

    if (denominator < 0)
    {
        m_denominator *= -1;
        m_numerator *= -1;
    }
}



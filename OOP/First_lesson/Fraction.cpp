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
void Fraction::print() const
{
    std::cout << m_numerator << '/' << m_denominator << std::endl;
}

void Fraction::input()
{
    std::cout << "Enter numerator and denominator: ";
    std::cin >> m_numerator >> m_denominator;

    while (m_denominator == 0)
    {
        std::cout << ("Denominator can't be zero! Please enter a valid denominator: ");
        std::cin >> m_denominator;
    }
}
int Fraction::getNumerator() const
{
    return m_numerator;
}

int Fraction::getDenominator() const
{
    return m_denominator;
}

void Fraction::setNumerator(const int value)
{
    m_numerator = value;
}

void Fraction::setDenominator(const int value)
{
    if (value == 0)
    {
        std::cout << "Fraction::Fraction: error: denominator is 0, result will be numerator/1.";
        m_denominator = 1;
    }
    else
    {
        m_denominator = value;
    }
}


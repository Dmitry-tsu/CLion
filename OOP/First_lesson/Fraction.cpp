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

Fraction Fraction::summation(const Fraction f) const
{
    Fraction c;
    c.m_numerator = m_numerator * f.m_denominator + f.m_numerator * m_denominator;
    c.m_denominator = m_denominator * f.m_denominator;
    return c;
}

Fraction Fraction::subtraction(const Fraction f) const
{
    Fraction c;
    c.m_numerator = m_numerator * f.m_denominator - f.m_numerator * m_denominator;
    c.m_denominator = m_denominator * f.m_denominator;
    return c;
}

Fraction Fraction::multiplication(const Fraction f) const
{
    Fraction c;
    c.m_numerator = m_numerator * f.m_numerator;
    c.m_denominator = m_denominator * f.m_denominator;
    return c;
}

Fraction Fraction::division(const Fraction f) const
{
    Fraction c;
    if (f.m_numerator == 0)
    {
        std::cerr << "The division operation is not possible because the numerator is 0."
                     " Result will be second fraction" << std::endl;
        return f;
    }
    c.m_numerator = m_numerator * f.m_denominator;
    c.m_denominator = m_denominator * f.m_numerator;
    return c;
}

int GCD(int numerator, int denominator)
{
    if (numerator == 0)
    {
        return 1;
    }

    while (numerator != denominator)
    {
        if (numerator > denominator)
        {
            numerator -= denominator;
        }
        else
        {
            denominator -= numerator;
        }
    }

    return numerator;
}

void Fraction::reduce()
{
    int gcd = GCD(m_numerator, m_denominator);
    m_numerator = m_numerator / gcd;
    m_denominator = m_denominator / gcd;
}

bool Fraction:: operator == (const Fraction other) const
{
    return (m_numerator == other.m_numerator && m_denominator == other.m_denominator);
}

bool Fraction:: operator != (const Fraction other) const
{
    return !operator == (other);
}

bool Fraction:: operator < (const Fraction other) const
{
    return ((m_numerator * other.m_denominator) < (other.m_numerator * m_denominator));
}

bool Fraction:: operator > (const Fraction other) const
{
    return ((m_numerator * other.m_denominator) > (other.m_numerator * m_denominator));
}

Fraction Fraction::operator+(const Fraction other) const
{
    return summation(other);
}

Fraction Fraction::operator-(const Fraction other) const
{
    return subtraction(other);
}

Fraction Fraction::operator*(const Fraction other) const {
    return multiplication(other);
}
Fraction Fraction::operator/(const Fraction other) const
{
    return division(other);
}

void Fraction::intToFraction(const int a)
{
    m_numerator = a;
    m_denominator = 1;
}

Fraction Fraction::sumFractionByInt(const int a) const
{
    Fraction f;
    f.intToFraction(a);
    return summation(f);
}

Fraction Fraction::operator+(const int a) const
{
    Fraction f;
    f.intToFraction(a);
    return summation(f);
}
void Fraction::exponentiation(const int degree) {
    int num = m_numerator;
    int den = m_denominator;

    if (degree == 0) {
        m_numerator = m_denominator = 1;
        return;
    }

    for (int i = 1; i < abs(degree); i++) {
        m_numerator *= num;
        m_denominator *= den;
    }

    if (degree < 0) {
        std::swap(m_numerator, m_denominator);
    }
}


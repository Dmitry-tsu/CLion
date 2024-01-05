
#pragma once

class Fraction
{
public:
    Fraction() = default;
    Fraction(const int numerator, const int denominator);
    ~Fraction() = default;

private:
    int m_numerator = 0;
    int m_denominator = 1;
};
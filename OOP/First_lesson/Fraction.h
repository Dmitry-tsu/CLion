
#pragma once

class Fraction
{
public:
    //
    Fraction() = default;
    Fraction(const int numerator, const int denominator);
    ~Fraction() = default;
    //
    void print() const;
    void input();
    //
    int getNumerator() const;
    int getDenominator() const;
    void setNumerator(const int numerator);
    void setDenominator(const int denominator);
    //

private:
    int m_numerator = 0;
    int m_denominator = 1;
};
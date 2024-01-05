
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
    Fraction summation(const Fraction other) const;
    Fraction subtraction(const Fraction other) const;
    Fraction multiplication(const Fraction other) const;
    Fraction division(const Fraction other) const;
    //
    void reduce();
    //
    bool operator==(const Fraction other) const;
    bool operator!=(const Fraction other) const;
    bool operator<(const Fraction other) const;
    bool operator>(const Fraction other) const;
    //
private:
    int m_numerator = 0;
    int m_denominator = 1;
};
#pragma once
class Fraction
{
public:
    Fraction();
    Fraction(int numerator, int denominaor);
    ~Fraction() = default;
    //Fraction sum(const Fraction a, const Fraction b);
    Fraction sum(const Fraction b);
    void print();
    Fraction subtraction(const Fraction b);
    Fraction multiplication(const Fraction b);
    Fraction division(const Fraction b);
    int numerator;
    int denominator;
};


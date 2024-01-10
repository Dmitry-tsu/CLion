#ifndef CLION_BOOLMATRIX_H
#define CLION_BOOLMATRIX_H
#include "/Users/diman4ik/CLion/OOP/Third_Lab/BoolVector.h"
//#include "/Users/diman4ik/CLion/OOP/Third_Lab/BoolVector.cpp"
#include <cstdint>
#include <iostream>
using SizeType = unsigned int;
class BoolMatrix
{

public:
    BoolMatrix();
    ~BoolMatrix();
    BoolMatrix(SizeType rows, SizeType cols, bool value);
    BoolMatrix(const BoolMatrix &other);
    BoolMatrix(char **matrix, SizeType rows, SizeType cols);

    void print()const;
    int returnRows() const;
    int returnCols() const;
    void swap(BoolMatrix &other);

    BoolVector &operator[](const int i);
    const BoolVector &operator[](const int i)const;

private:
    SizeType rows = 0;
    SizeType cols = 0;
    BoolVector *bm=nullptr;
};

std::ostream& operator<<(std::ostream &stream, const BoolMatrix &bmatr);
std::istream& operator>>(std::istream &stream, BoolMatrix &bmatr);


#endif //CLION_BOOLMATRIX_H
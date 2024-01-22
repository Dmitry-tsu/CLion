#ifndef CLION_BOOLMATRIX_H
#define CLION_BOOLMATRIX_H
#include "../../CLion/OOP/Third_Lab/BoolVector.h"
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
    void set1(const SizeType i, const SizeType j, const SizeType count=0);
    void set0(const SizeType i, const SizeType j, const SizeType count=0);

    int returnWeight() const;
    int returnWeight(const SizeType index);
    BoolVector logicalAnd() const;
    BoolVector logicalOr() const;
    void inverse(const SizeType i, const SizeType j, const SizeType count=0);


    BoolVector &operator[](const SizeType i);
    const BoolVector &operator[](const SizeType i)const;
    BoolMatrix operator=(const BoolMatrix &other);
    BoolMatrix operator&(const BoolMatrix &other) const;
    BoolMatrix operator&=(const BoolMatrix &other);
    BoolMatrix operator|(const BoolMatrix &other) const;
    BoolMatrix operator|=(const BoolMatrix &other);
    BoolMatrix operator^(const BoolMatrix &other) const;
    BoolMatrix operator^=(const BoolMatrix &other);
    BoolMatrix operator~() const;

private:
    SizeType rows = 0;
    SizeType cols = 0;
    BoolVector *bm=nullptr;
};

std::ostream& operator<<(std::ostream &stream, const BoolMatrix &matrix);
std::istream& operator>>(std::istream &stream, BoolMatrix &matrix);


#endif //CLION_BOOLMATRIX_H
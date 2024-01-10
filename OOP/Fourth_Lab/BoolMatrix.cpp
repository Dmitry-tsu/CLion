#include "BoolMatrix.h"
#include "/Users/diman4ik/Error/untitled3/BoolVector.cpp"
#include "/Users/diman4ik/Error/untitled3/BoolVector.h"
#include <cstdint>
#include<iostream>
#include <cassert>

using SizeType = unsigned int;

BoolMatrix::BoolMatrix()
        :BoolMatrix(1, 8, false)
{}

BoolMatrix::~BoolMatrix()
{
    delete[]bm;
}

BoolMatrix::BoolMatrix(SizeType Rows, SizeType Cols, bool value)
        :rows(Rows), cols(Cols)
{
    rows = Rows;
    cols = Cols;
    bm = new BoolVector[rows];
    BoolVector vec(cols, value);
    for (int i = 0; i < rows; i++)
    {
        bm[i] = vec;
    }
}

BoolMatrix::BoolMatrix(const BoolMatrix &other)
        :rows(other.rows), cols(other.cols)
{
    bm = new BoolVector[rows];
    for (int i = 0; i < rows; i++)
        bm[i] = other.bm[i];

}

BoolMatrix::BoolMatrix(char **matrix, SizeType Rows, SizeType Cols)
        :rows(Rows), cols(Cols)
{
    bm = new BoolVector[rows];
    for (int i = 0; i < rows; i++)
        bm[i] = matrix[i];
}

void BoolMatrix::print()const
{
    for (int i = 0; i < rows; i++)
    {
        std::cout << bm[i];
    }
}


int BoolMatrix::returnRows() const
{
    return rows;
}

int BoolMatrix::returnCols() const
{
    return cols;
}

void BoolMatrix::swap(BoolMatrix& other)
{
    std::swap(rows, other.rows);
    std::swap(cols, other.cols);
    std::swap(bm, other.bm);
}

void BoolMatrix::set1(const SizeType i, const SizeType j, const SizeType count)
{
    for (int u = j; u < j + count && u < cols; u++)
        bm[i][u]=1;
}

void BoolMatrix::set0(const SizeType i, const SizeType j, const SizeType count)
{
    for (int u = j; u < j + count && u < cols; u++)
        bm[i][u]=0;
}

BoolVector& BoolMatrix::operator[](const int i)
{
    assert(i >= 0 || i < rows);
    return bm[i];
}

const BoolVector& BoolMatrix::operator[](const int i) const
{
    assert(i >= 0 || i < rows);
    return bm[i];
}

std::ostream& operator<<(std::ostream &stream, const BoolMatrix &matrix)
{
    for (int i = 0; i < matrix.returnRows(); i++)
        stream << matrix[i];
    return stream;
}

std::istream& operator>>(std::istream &stream, BoolMatrix &matrix)
{
    for (int i = 0; i < matrix.returnRows(); i++)
        stream >> matrix[i];
    return stream;
}
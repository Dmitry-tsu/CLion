#include "BoolMatrix.h"
#include "../../CLion/OOP/Third_Lab/BoolVector.cpp"
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
    for (int u = j; u <= j + count && u < cols; u++)
        bm[i][u]=1;
}

void BoolMatrix::set0(const SizeType i, const SizeType j, const SizeType count)
{
    for (int u = j; u <= j + count && u < cols; u++)
        bm[i][u]=0;
}

int BoolMatrix::returnWeight() const
{
    int totalWeight = 0;
    for (int i = 0; i < rows; i++)
        totalWeight += bm[i].returnWeight();
    return totalWeight;
}

int BoolMatrix::returnWeight(const SizeType index)
{
    return bm[index].returnWeight();
}

BoolVector BoolMatrix::logicalAnd() const
{
    BoolVector result = bm[0];
    for (int i = 1; i < rows; i++)
        result &= bm[i];
    return result;
}

BoolVector BoolMatrix::logicalOr() const
{
    BoolVector result = bm[0];
    for (int i = 1; i < rows; i++)
        result |= bm[i];
    return result;
}

void BoolMatrix::inverse(const SizeType i, const SizeType j, const SizeType count)
{
    for(int u = j; u <= j + count && u < cols; u++)
        bm[i][u] = ~bm[i][u];
}

BoolVector& BoolMatrix::operator[](const SizeType i)
{
    assert(i >= 0 && i < rows);
    return bm[i];
}

const BoolVector& BoolMatrix::operator[](const SizeType i) const
{
    assert(i >= 0 && i < rows);
    return bm[i];
}

BoolMatrix BoolMatrix::operator=(const BoolMatrix &other)
{
    if (bm == other.bm) return *this;
    if (rows != other.rows)
    {
        rows = other.rows;
        delete[] bm;
        bm = new BoolVector[rows];
    }
    cols = other.cols;
    for (int i = 0; i < rows; i++)
    {
        bm[i] = other.bm[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix &other) const
{
    SizeType resultRows = std::max(rows, other.rows);
    SizeType resultCols = std::max(cols, other.cols);
    BoolMatrix matrix(resultRows, resultCols, false);
    for (int i = 0; i < resultRows; i++)
        matrix.bm[i] = bm[i] & other.bm[i];
    return matrix;
}

BoolMatrix BoolMatrix::operator&=(const BoolMatrix &other)
{
    BoolMatrix tmp(*this & other);
    swap(tmp);
    return *this;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix &other) const
{
    SizeType resultRows = std::max(rows, other.rows);
    SizeType resultCols = std::max(cols, other.cols);
    BoolMatrix resultMatrix(resultRows, resultCols, false);
    SizeType commonRows = std::max(rows, other.rows);
    for (int i = 0; i < commonRows; i++)
        resultMatrix.bm[i] = bm[i] ^ other.bm[i];
    for (int i = commonRows; i < rows; i++)
        resultMatrix.bm[i] = bm[i];
    for (int i = commonRows; i < other.rows; i++)
        resultMatrix.bm[i] = other.bm[i];
    return resultMatrix;
}

BoolMatrix BoolMatrix::operator|=(const BoolMatrix& other)
{
    BoolMatrix tmp(*this | other);
    swap(tmp);
    return *this;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix &other) const
{
    SizeType resultRows = std::max(rows, other.rows);
    SizeType resultCols = std::max(cols, other.cols);
    BoolMatrix resultMatrix(resultRows, resultCols, false);
    SizeType commonRows = std::max(rows, other.rows);
    for (int i = 0; i < commonRows; i++)
        resultMatrix.bm[i] = bm[i] ^ other.bm[i];
    for (int i = commonRows; i < rows; i++)
        resultMatrix.bm[i] = bm[i];
    for (int i = commonRows; i < other.rows; i++)
        resultMatrix.bm[i] = other.bm[i];
    return resultMatrix;
}


BoolMatrix BoolMatrix::operator^=(const BoolMatrix &other)
{
    BoolMatrix tmp(*this | other);
    swap(tmp);
    return *this;
}

BoolMatrix BoolMatrix::operator~() const
{
    BoolMatrix matrix(*this);
    for (int i = 0; i < rows; i++)
        matrix.bm[i].inverse();
    return matrix;
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
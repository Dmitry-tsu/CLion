#include "BoolVector.h"
#include <iostream>

BoolVector::BoolVector()
{
    length = cellSize;
    cellCount = length / 8 + (length % 8 > 0);
    data = new Byte[cellCount]();
}

BoolVector::BoolVector(const SizeType length, const bool value)
{
    this->length = length;
    cellCount = length / 8 + (length % 8 > 0);
    insignificantPart = cellSize * cellCount - length;
    data = new Byte[cellCount]();

    Byte mask = 0;
    if (value)
        mask = 0xFF;

    for (int i = 0; i < cellCount; i++)
    {
        data[i] = mask;
    }
    data[cellCount - 1] = data[cellCount - 1] >> insignificantPart;
    data[cellCount - 1] = data[cellCount - 1] << insignificantPart;
}

void BoolVector::printCell(const int &cell) const
{
    for (Byte i = 128; i > 0; i >>= 1)
    {
        if (data[cell] & i)
            std::cout << "1 ";
        else
            std::cout << "0 ";
    }
}

void BoolVector::print() const
{
    for (int i = 0; i < cellCount; i++)
    {
        std::cout << "[ ";
        printCell(i);
        std::cout << "]";
    }
    std::cout << std::endl;
}

BoolVector::~BoolVector()
{
    delete[] data;
}

BoolVector::BoolVector(const BoolVector &other)
        : length(other.length)
{
    cellCount = other.cellCount;
    data = new Byte[cellCount];
    insignificantPart = (cellCount * cellSize) - length;
    for (int i = 0; i < cellCount; i++)
    {
        data[i] = other.data[i];
    }
}

BoolVector::BoolVector(const char *data)
{
    length = strlen(data);
    cellCount = length / 8 + (length % 8 > 0);
    insignificantPart = cellSize * cellCount - length;
    this->data = new Byte[cellCount]();
    for (int i = 0; i < length; i++)
    {
        if (data[i] == '1')
            set1(i / cellSize, i % cellSize);
        else
            set0(i / cellSize, i % cellSize);
    }
    this->data[cellCount - 1] = this->data[cellCount - 1] >> insignificantPart;
    this->data[cellCount - 1] = this->data[cellCount - 1] << insignificantPart;
}

int BoolVector::lenght()
{
    return 0;
}

void BoolVector::set1(const int &cell, const int &pos) const
{
    Byte mask = 1;
    mask = mask << (cellSize - 1 - pos);
    data[cell] = data[cell] | mask;
}

void BoolVector::set0(const int &cell, const int &pos) const
{
    Byte mask = 1;
    mask = mask << (cellSize - 1 - pos);
    data[cell] = data[cell] & ~mask;
}

void BoolVector::swap(BoolVector &other)
{
    std::swap(length, other.length);
    std::swap(cellCount, other.cellCount);
    std::swap(insignificantPart, other.insignificantPart);
    std::swap(data, other.data);
}
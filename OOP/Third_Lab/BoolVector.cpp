#include "BoolVector.h"
#include<iostream>
#include <cassert>

BoolVector::BoolVector()
{
    length = cellSize;
    cellCount = length / 8 + (length % 8 > 0);
    data = new Byte[cellCount];
    data[0] = false;
}

BoolVector::BoolVector(const char* _data)
{
    length = strlen(_data);
    cellCount = length / 8 + (length % 8 > 0);
    insignificantPart = cellSize * cellCount - length;
    data = new Byte[cellCount];
    for (int i = 0; i < length; i++)
    {
        if (_data[i] == '1')
            set1(i / cellSize, i % cellSize);
        else
            set0(i / cellSize, i % cellSize);
    }
    shift();
}

BoolVector::BoolVector(const BoolVector& other)
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
    shift();
}

BoolVector::~BoolVector()
{
    delete[]data;
}

void BoolVector::shift()
{
    data[cellCount - 1] = data[cellCount - 1] >> insignificantPart;
    data[cellCount - 1] = data[cellCount - 1] << insignificantPart;
}

void BoolVector::printCell(const int& cell)const
{

    for (uint8_t i = 128; i > 0; i >>= 1)
    {
        if (data[cell] & i)
            std::cout << "1 ";
        else
            std::cout << "0 ";
    }
}

void BoolVector::print()const
{
    for (int i = 0; i < cellCount; i++)
    {
        std::cout << "[ ";
        printCell(i);
        std::cout << "]";
    }
    std::cout << std::endl;
}

int BoolVector::returnLength() const
{
    return length;
}

int BoolVector::getByteCount() const
{
    return cellCount;
}

void BoolVector::inverse()
{
    for (int i = 0; i < length; i++)
    {
        BoolVector a(*this);
        if (a[i])
            set0(i / cellSize, i % cellSize);
        else
            set1(i / cellSize, i % cellSize);
    }

}

void  BoolVector::set1(const int& cell, const int& pos)const
{
    uint8_t mask = 1;
    mask = mask << (7-pos);
    data[cell] = data[cell] | mask;
}

void  BoolVector::set0(const int& cell, const int& pos)const
{
    uint8_t mask = 1;
    mask = mask<< (7-pos);
    data[cell] = data[cell] & ~mask;
}

void BoolVector::swap(BoolVector& other)
{
    std::swap(length, other.length);
    std::swap(cellCount, other.cellCount);
    std::swap(insignificantPart, other.insignificantPart);
    std::swap(data, other.data);
}

bool& BoolVector::operator[](const int index)
{
    assert(index >= 0 && index < cellSize * cellCount);
    uint8_t mask = 1;
    mask = mask << (7 - index % cellSize);
    bool value = data[index / cellSize] & mask;
    return static_cast<bool &>(value);
}

const bool& BoolVector::operator[](const int index) const
{
    assert(index >= 0 && index < cellSize * cellCount);
    uint8_t mask = 1;
    mask = mask << (7 - index % cellSize);
    bool value = data[index / cellSize] & mask;
    return value;
}

std::ostream& operator<<(std::ostream& stream, const BoolVector& bvec)
{
    int n = 0;
    for (int i = 0; i < bvec.getByteCount(); i++)
    {
        stream << "[ ";
        for (int j = 0; j < bvec.cellSize; j++)
            stream << bvec[n++]<<" ";
        stream << "]";
    }
    std::cout << std::endl;
    return stream;
}

std::istream& operator >> (std::istream& stream, BoolVector& bvec)
{
    char s;
    for (int i = 0; i < bvec.returnLength(); i++)
    {
        stream >> s;
        if (s == '1')
            bvec.set1(i / bvec.cellSize, i % bvec.cellSize);
        else
            bvec.set0(i / bvec.cellSize, i % bvec.cellSize);
    }
    return stream;
}


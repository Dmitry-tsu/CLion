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
        if (rank(i).value)
            rank(i).set0();
        else
            rank(i).set1();
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

BoolRank& BoolVector::operator[](const int index)
{
    assert(index >= 0 && index < cellSize * cellCount);
    BoolRank rank(data,index);
    return static_cast<BoolRank &>(rank);
}

const BoolRank& BoolVector::operator[](const int index) const
{
    assert(index >= 0 && index < cellSize * cellCount);
    BoolRank rank(data, index);
    return rank;
}

BoolVector BoolVector::operator^(const BoolVector& other) const
{
    BoolVector bvec = (std::max(length, other.length));
    int min = std::min(cellCount, other.cellCount);
    for (int i = 0; i < min; i++)
        bvec.data[i] = data[i] ^ other.data[i];
    for (int i = min; i < cellCount; i++)
        bvec.data[i] = data[i];
    for (int i = min; i < other.cellCount; i++)
        bvec.data[i] = other.data[i];
    return bvec;
}

BoolVector &BoolVector::operator^=(const BoolVector& other)
{
    BoolVector tmp(*this ^ other);
    swap(tmp);
    return *this;
}

BoolVector BoolVector::operator~() const
{
    BoolVector bvec(length);
    for (int i = 0; i < cellCount; i++)
        bvec.data[i] = ~data[i];
    bvec.shift();
    return bvec;
}

BoolVector &BoolVector::operator=(BoolVector &&other)
{
    swap(other);
    return *this;
}

BoolVector &BoolVector::operator=(const BoolVector &other)
{
    if (this == &other) return *this;

    if (length != other.length)
    {
        length = other.length;
        cellCount = other.cellCount;
        insignificantPart = other.insignificantPart;
    }
    delete[] data;
    data = new Byte[length];
    for (int i = 0; i < cellCount; i++)
        data[i] = other.data[i];
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector &other) const
{
    BoolVector bvec = (std::max(length, other.length));
    int min = std::min(cellCount, other.cellCount);
    for (int i = 0; i < min; i++)
        bvec.data[i] = data[i] & other.data[i];
    return bvec;
}

BoolVector &BoolVector::operator&=(const BoolVector &other)
{
    BoolVector tmp(*this & other);
    swap(tmp);
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector &other) const
{
    BoolVector bvec = (std::max(length, other.length));
    int min = std::min(cellCount, other.cellCount);
    for (int i = 0; i < min; i++)
        bvec.data[i] = data[i] | other.data[i];
    for (int i = min; i < cellCount; i++)
        bvec.data[i] = data[i];
    for (int i = min; i < other.cellCount; i++)
        bvec.data[i] = other.data[i];
    return bvec;
}

BoolVector &BoolVector::operator|=(const BoolVector &other)
{
    BoolVector tmp(*this | other);
    swap(tmp);
    return *this;
}

BoolVector BoolVector::operator<<(const int& count) const
{
    int shift_amount = count;
    if (count > length)
        shift_amount = length;

    BoolVector bvec = *this;
    if (shift_amount > cellSize)
    {
        for (int i = 0; i + (shift_amount / cellSize) < cellCount; i++)
        {
            bvec.data[i] = data[i + (shift_amount / cellSize)];
            bvec.data[i + (shift_amount / cellSize)] = false;
        }
    }

    uint8_t mask = 1;
    for (int j = 0; j < (shift_amount % cellSize); j++)
        mask |= mask << 1;
    mask <<= cellSize - (shift_amount % cellSize);
    for (int i = 0; i < cellCount - (shift_amount / cellSize) - 1; i++)
    {
        uint8_t mask_cu = mask;
        bvec.data[i] = bvec.data[i] << (shift_amount % cellSize);
        mask_cu &= bvec.data[i + 1];
        mask_cu >>= cellSize - (shift_amount % cellSize);
        bvec.data[i] |= mask_cu;
    }
    bvec.data[cellCount - (shift_amount / cellSize) - 1] = bvec.data[cellCount - (shift_amount / cellSize) - 1] << shift_amount;
    return bvec;
}

BoolVector& BoolVector::operator<<=(const int& count)
{
    BoolVector tmp(*this << count);
    swap(tmp);
    return *this;
}


BoolVector BoolVector::operator>>(const int& count) const
{
    int shift_amount = count;
    if (count > length)
        shift_amount = length;

    BoolVector bvec = *this;
    int n = 1;
    if (shift_amount > cellSize)
    {
        for (int i = cellCount-1; i - (shift_amount / cellSize) >= 0; i--)
        {
            bvec.data[i] = data[i - (shift_amount / cellSize)];
            bvec.data[i - (shift_amount / cellSize)] = false;
        }
    }
    uint8_t mask = 1;
    for (int j = 0; j < (shift_amount % cellSize) - 1; j++)
        mask |= mask << 1;

    for (int i = cellCount - 1; i >(shift_amount / cellSize); i--)
    {
        uint8_t mask_cu = mask;
        bvec.data[i] = bvec.data[i] >> (shift_amount % cellSize);
        mask_cu &= bvec.data[i - 1];
        mask_cu <<= cellSize - (shift_amount % cellSize);
        bvec.data[i] |= mask_cu;
    }
    bvec.data[shift_amount / cellSize] = bvec.data[shift_amount / cellSize] >> shift_amount;
    bvec.shift();
    return bvec;
}

BoolVector& BoolVector::operator>>=(const int& count)
{
    BoolVector tmp(*this >> count);
    swap(tmp);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const BoolVector &bvec)
{
    int n = 0;
    for (int i = 0; i < bvec.getByteCount(); i++)
    {
        stream << "[ ";
        for (int j = 0; j < bvec.cellSize; j++)
            stream << bvec[n++] << " ";
        stream << "]";
    }
    std::cout << std::endl;
    return stream;
}

std::istream &operator>>(std::istream &stream, BoolVector &bvec)
{
    char s;
    for (int i = 0; i < bvec.returnLength(); i++)
    {
        stream >> s;
        if (s == '0')
            bvec.set0(i / bvec.cellSize, i % bvec.cellSize);
        else
            bvec.set1(i / bvec.cellSize, i % bvec.cellSize);
    }
    return stream;
}


BoolRank BoolVector::rank(const int& index)
{
    BoolRank r(data, index);
    return r;
}

//BoolRank::
BoolRank::BoolRank()
{
    cell = 0;
    mask = 0;
    data = nullptr;
    value =false;
}
BoolRank::BoolRank(Byte* _data, const int& index)
{
    cell = index / 8;
    mask = 1;
    mask <<= 7 - index % 8;
    data = _data;
    value = data[cell] & mask;
}

void BoolRank::set1()
{
    data[cell] = data[cell] | mask;
    value = data[cell] & mask;
}

void BoolRank::set0()
{
    data[cell] = data[cell] & ~mask;
    value = data[cell] & mask;
}

BoolRank &BoolRank::operator=(const int& _value)
{
    return *this;
}

std::ostream &operator<<(std::ostream& stream, const BoolRank& _rank)
{
    stream << _rank.value;
    return stream;
}

std::istream &operator>>(std::istream& stream, BoolRank& _rank)
{
    char s;
    stream >> s;
    if (s == '0')
        _rank.set0();
    else
        _rank.set1();

    return stream;
}
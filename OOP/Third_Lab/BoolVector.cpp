#include "BoolVector.h"
#include<iostream>
#include <cassert>

BoolVector::BoolVector()
        : BoolVector(8, false)
{}

BoolVector::BoolVector(const char *Data)
{
    length = strlen(Data);
    cellCount = length / 8 + (length % 8 > 0);
    insignificantPart = cellSize * cellCount - length;
    data = new Byte[cellCount];
    for (int i = 0; i < length; i++)
    {
        if (Data[i] == '1')
            set1(i);
        else
            set0(i);
    }
    shift();
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

void BoolVector::printCell(const int cell) const
{

    for (uint8_t i = 128; i > 0; i >>= 1)
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

int BoolVector::returnLength() const
{
    return length;
}

int BoolVector::returnCellCount() const
{
    return cellCount;
}

void BoolVector::inverse()
{
    for (int i = 0; i < cellCount; i++)
        data[i] = ~data[i];
    shift();
}


void  BoolVector::set1(const int i)
{
    int cell = i / cellSize;
    int pos = i % cellSize;
    uint8_t mask = 1;
    mask = mask << (7-pos);
    data[cell] = data[cell] | mask;
}

void  BoolVector::set0(const int i)
{
    int cell = i / cellSize;
    int pos = i % cellSize;
    uint8_t mask = 1;
    mask = mask << (7-pos);
    data[cell] = data[cell] & ~mask;
}

void BoolVector::swap(BoolVector &other)
{
    std::swap(length, other.length);
    std::swap(cellCount, other.cellCount);
    std::swap(insignificantPart, other.insignificantPart);
    std::swap(data, other.data);
}

void BoolVector::inverse(const int i)
{
    if ((*this)[i])
        set0(i);
    else
        set1(i);
}

int BoolVector::returnWeight()
{
    int w = 0;
    for (int i = 0; i < cellCount; i++)
    {
        uint8_t mask = 1;
        mask <<= 7;
        for (int j = 0; j < cellSize; j++)
        {
            if (data[i] & mask)
                w++;
            mask >>= 1;
        }
    }
    return w;
}

void BoolVector::set1(const int pos, const int count)
{
    for (int i = pos; i < length && i < pos + count; i++)
        (*this)[i] = 1;
}

void BoolVector::set0(const int pos, const int count)
{
    for (int i = pos; i < length && i < pos + count; i++)
        (*this)[i] = 0;
}

void BoolVector::set1()
{
    uint8_t mask = 0;
    for (int i = 0; i < cellCount; i++)
        data[i] = ~mask;
    shift();
}

void BoolVector::set0()
{
    uint8_t mask = 0;
    for (int i = 0; i < cellCount; i++)
        data[i] = mask;
}

BoolVector::BoolRank BoolVector::operator[](const int index)
{
    assert(index >= 0 && index < cellSize * cellCount);
    BoolRank rank(data,index);
    return rank;
}

const BoolVector::BoolRank BoolVector::operator[](const int index) const
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

BoolVector &BoolVector::operator^=(const BoolVector &other)
{
    BoolVector tmp(*this ^ other);
    swap(tmp);
    return *this;
}

BoolVector BoolVector::operator~() const
{
    BoolVector bvec(length);
    bvec.inverse();
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
        delete[] data;
        data = new Byte[length];
    }
    for (int i = 0; i < cellCount; i++)
        data[i] = other.data[i];
    return *this;
}

BoolVector BoolVector::operator&(const BoolVector &other) const
{
    BoolVector bvec = (std::min(length, other.length));
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
// shift_amount / currentCellMask
BoolVector BoolVector::operator<<(int count) const
{
    if (count > length)
        count = length;

    BoolVector bvec = *this;
    if (count >= cellSize)
    {
        for (int i = 0; i + (count / cellSize) < bvec.cellCount; i++)
            bvec.data[i] = data[i + (count / cellSize)];
        for (int i = bvec.cellCount-1; i >= bvec.cellCount-(count / cellSize); i--)
            bvec.data[i] = false;

        count = count % cellSize;
    }
    if (count > 0)
    {
        uint8_t mask = 0;
        mask = ~mask;
        mask <<= cellSize - count;
        for (int i = 0; i < cellCount - 1; i++)
        {
            uint8_t currentCellMask = mask;
            bvec.data[i] = bvec.data[i] << count;
            currentCellMask &= bvec.data[i + 1];
            currentCellMask >>= cellSize - count;
            bvec.data[i] |= currentCellMask;
        }
        bvec.data[cellCount - 1]  <<= count;
    }
    return bvec;
}

BoolVector& BoolVector::operator<<=(const int count)
{
    BoolVector tmp(*this << count);
    swap(tmp);
    return *this;
}


BoolVector BoolVector::operator>>(int count) const
{
    if (count > length)
        count = length;

    BoolVector bvec = *this;
    int n = 1;
    if (count >= cellSize)
    {
        for (int i = cellCount - 1; i - (count / cellSize) >= 0; i--)
            bvec.data[i] = data[i - (count / cellSize)];

        for (int i = 0; i <= count / cellSize -1; i++)
            bvec.data[i] = false;

        count = count % cellSize;
    }
    if (count)
    {
        uint8_t mask = 0;
        mask = ~mask;
        mask >>= cellSize - count;

        for (int i = cellCount - 1; i > 0; i--)
        {
            uint8_t currentCellMask = mask;
            bvec.data[i] = bvec.data[i] >> count;
            currentCellMask &= bvec.data[i - 1];
            currentCellMask <<= cellSize - count;
            bvec.data[i] |= currentCellMask;
        }
        bvec.data[0] >>= count;
    }
    bvec.shift();
    return bvec;
}


BoolVector& BoolVector::operator>>=(const int count)
{
    BoolVector tmp(*this >> count);
    swap(tmp);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const BoolVector &bvec)
{
    int n = 0;
    for (int i = 0; i < bvec.returnCellCount(); i++)
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
            bvec.set0(i);
        else
            bvec.set1(i);
    }
    return stream;
}

//
BoolVector::BoolRank::BoolRank()
{
    cell = 0;
    mask = 0;
    data = nullptr;
    value =false;
}

BoolVector::BoolRank::BoolRank(Byte *Data, const int Index)
{
    cell = Index / 8;
    mask = 1;
    mask <<= 7 - Index % 8;
    data = Data;
    value = data[cell] & mask;
}

BoolVector::BoolRank::BoolRank(const BoolRank &other)
{
    cell = other.cell;
    mask = other.mask;
    value = other.value;
    data = other.data;
}

void BoolVector::BoolRank::set1()
{
    data[cell] = data[cell] | mask;
    value = data[cell] & mask;
}

void BoolVector::BoolRank::set0()
{
    data[cell] = data[cell] & ~mask;
    value = data[cell] & mask;
}

bool BoolVector::BoolRank::returnValue() const
{
    return value;
}

BoolVector::BoolRank &BoolVector::BoolRank::operator=(const int Value)
{
    if (bool(Value))
        set1();
    else
        set0();
    return *this;
}

BoolVector::BoolRank& BoolVector::BoolRank::operator=(const BoolRank &other)
{
    operator=((int)other);
    return *this;
}

std::ostream &operator<<(std::ostream &Stream, const BoolVector::BoolRank &Rank)
{
    Stream << Rank.returnValue();
    return Stream;
}

std::istream &operator>>(std::istream &Stream, BoolVector::BoolRank Rank)
{
    char s;
    Stream >> s;
    if (s == '0')
        Rank.set0();
    else
        Rank.set1();
    return Stream;
}

BoolVector::BoolRank::operator int()const
{
    int val = int(value);
    return val;
}

BoolVector::BoolRank::operator bool()const
{
    bool val = value;
    return val;
}

bool BoolVector::BoolRank::operator&(const int Value)const
{
    bool ans = value && bool(Value);
    return ans;

}

BoolVector::BoolRank BoolVector::BoolRank::operator&=(const int Value)
{
    bool ans = value && bool(Value);
    if (ans)
        set1();
    else
        set0();
    return *this;
}

bool BoolVector::BoolRank::operator|(const int Value)const
{
    bool ans = value || bool(Value);
    return ans;
}

BoolVector::BoolRank BoolVector::BoolRank::operator|=(const int Value)
{
    bool ans = Value || bool(value);
    if (ans)
        set1();
    else
        set0();
    return *this;
}

bool BoolVector::BoolRank::operator~() const
{
    bool ans = !value;
    return ans;
}

bool BoolVector::BoolRank::operator^(const int Value)const
{
    bool ans = Value ^ bool(value);
    return ans;
}

BoolVector::BoolRank BoolVector::BoolRank::operator^=(const int Value)
{
    bool ans = Value ^ bool(Value);
    if (ans)
        set1();
    else
        set0();
    return *this;
}

bool BoolVector::BoolRank::operator==(const bool Value)const
{
    if (value == Value)
        return true;
    return false;
}

bool BoolVector::BoolRank::operator!=(const bool Value)const
{
    if (value !=Value)
        return true;
    return false;
}

bool BoolVector::BoolRank::operator>(const bool Value)const
{
    if (value > Value)
        return true;
    return false;
}

bool BoolVector::BoolRank::operator<(const bool Value)const
{
    if (value < Value)
        return true;
    return false;
}

bool BoolVector::BoolRank::operator>=(const bool Value)const
{
    if (value >= Value)
        return true;
    return false;
}

bool BoolVector::BoolRank::operator<=(const bool Value)const
{
    if (value <= Value)
        return true;
    return false;
}

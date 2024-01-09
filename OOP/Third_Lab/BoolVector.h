#ifndef CLION_BOOLVECTOR_H
#define CLION_BOOLVECTOR_H
#include <cstdint>
#include <iostream>
#include<cstdint>
#include<iostream>
class BoolRank;
class BoolVector
{
public:
    using SizeType = unsigned int;
    using Byte = unsigned char;
    const uint8_t cellSize = 8;

    BoolVector();
    BoolVector(const char *data);
    BoolVector(const BoolVector &other);
    BoolVector(const SizeType length, const bool value = false);
    ~BoolVector();
    void shift();
    void printCell(const int &number_cell)const;
    void print()const;
    int returnLength()const;
    int getByteCount()const;
    void inverse();
    void set1(const int &cell, const int& pos)const;
    void set0(const int &cell, const int& pos)const;
    void swap(BoolVector &other);

    BoolRank &operator[](const int index);
    const BoolRank &operator[](const int index)const;

    BoolVector operator^(const BoolVector& other) const;
    BoolVector &operator^=(const BoolVector& other);
    BoolVector operator~() const;

    BoolVector &operator=(BoolVector &&other);
    BoolVector &operator=(const BoolVector &other);
    BoolVector operator&(const BoolVector &other) const;
    BoolVector &operator&=(const BoolVector &other);
    BoolVector operator|(const BoolVector &other) const;
    BoolVector &operator|=(const BoolVector &other);

    BoolVector operator<<(const int &count) const;
    BoolVector &operator<<=(const int &count);
    BoolVector operator>>(const int &count) const;
    BoolVector &operator>>=(const int &count);

private:
    SizeType length = 0;
    SizeType cellCount = 0;
    uint8_t insignificantPart = 0;
    Byte *data = nullptr;
    BoolRank rank( const int &index=0);
    friend BoolRank;
};

std::ostream& operator<<(std::ostream &stream, const BoolVector &bvec);
std::istream& operator>>(std::istream &stream, BoolVector &bvec);


class BoolRank
{
    using Byte = unsigned char;
private:
    uint8_t mask = 0;
    int cell = 0;
    Byte* data = nullptr;
public:
    bool value = false;
    BoolRank();
    BoolRank(Byte *_data, const int &index = 0);

    void set1();
    void set0();
    BoolRank& operator=(const int &value);

};
std::ostream &operator<<(std::ostream &stream, const BoolRank &rank);
std::istream &operator>>(std::istream &stream, BoolRank &rank);

#endif //CLION_BOOLVECTOR_H
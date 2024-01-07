#ifndef CLION_BOOLVECTOR_H
#define CLION_BOOLVECTOR_H
#include <cstdint>
#include <iostream>
#include<stdint.h>
#include<iostream>
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
    bool &operator[](const int index);
    const bool &operator[](const int index)const;

    BoolVector operator^(const BoolVector& other) const;
    BoolVector& operator^=(const BoolVector& other);
    BoolVector operator~() const;

    BoolVector &operator=(BoolVector &&other);
    BoolVector &operator=(const BoolVector &other);
    BoolVector operator&(const BoolVector &other) const;
    BoolVector &operator&=(const BoolVector &other);
    BoolVector operator|(const BoolVector &other) const;
    BoolVector &operator|=(const BoolVector &other);

private:
    SizeType length = 0;
    SizeType cellCount = 0;
    uint8_t insignificantPart = 0;
    Byte *data = nullptr;
};

std::ostream& operator<<(std::ostream& stream, const BoolVector& bvec);
std::istream& operator>>(std::istream& stream, BoolVector& bvec);

#endif //CLION_BOOLVECTOR_H
#ifndef CLION_BOOLVECTOR_H
#define CLION_BOOLVECTOR_H
#include <cstdint>
#include <iostream>
#include<cstdint>
#include<iostream>

class BoolVector
{
private:
    class BoolRank;
public:
    using SizeType = unsigned int;
    using Byte = unsigned char;
    const uint8_t cellSize = 8;

    BoolVector();
    BoolVector(const char *data);
    BoolVector(const BoolVector &other);
    BoolVector(const SizeType length, const bool value = false);
    ~BoolVector();
    void printCell(const int number_cell)const;
    void print()const;
    int returnLength()const;
    int returnCellCount()const;
    void inverse();
    void set1(const int i);
    void set0(const int i);
    void swap(BoolVector &other);


    void inverse(const int i);
    int returnWeight();
    void set1(const int position, const int count);
    void set0(const int position, const int count);
    void set1();
    void set0();

    BoolRank operator[](const int index);
    const BoolRank operator[](const int index)const;

    BoolVector operator^(const BoolVector& other) const;
    BoolVector &operator^=(const BoolVector& other);
    BoolVector operator~() const;

    BoolVector &operator=(BoolVector &&other);
    BoolVector &operator=(const BoolVector &other);
    BoolVector operator&(const BoolVector &other) const;
    BoolVector &operator&=(const BoolVector &other);
    BoolVector operator|(const BoolVector &other) const;
    BoolVector &operator|=(const BoolVector &other);

    BoolVector operator<<(int count) const;
    BoolVector &operator<<=(const int count);
    BoolVector operator>>(int count) const;
    BoolVector &operator>>=(const int count);

    friend std::ostream& operator<<(std::ostream &stream, const BoolRank &rank);
    friend std::istream& operator>>(std::istream &stream, BoolRank rank);


private:
    SizeType length = 0;
    SizeType cellCount = 0;
    uint8_t insignificantPart = 0;
    Byte *data = nullptr;
    void shift();
};

std::ostream &operator<<(std::ostream &stream, const BoolVector &bvec);
std::istream& operator>>(std::istream &stream, BoolVector &bvec);


class BoolVector::BoolRank
{
    using Byte = unsigned char;
private:
    uint8_t mask = 0;
    int cell = 0;
    Byte* data = nullptr;
    bool value = false;
public:

    BoolRank();
    BoolRank(Byte *Data, const int index = 0);
    BoolRank(const BoolRank &other);

    void set1();
    void set0();
    //void swap(BoolRank &other);
    bool returnValue() const;

    BoolRank &operator=(const int value);
    BoolRank &operator=(const BoolRank &other);
    bool operator==(const bool value)const;
    bool operator!=(const bool value)const;

    operator int()const;
    operator bool()const;

    bool operator&(const int value)const;
    BoolRank operator&=(const int value);
    bool operator|(const int value)const;
    BoolRank operator|=(const int value);
    bool operator~() const;
    bool operator^(const int value)const;
    BoolRank operator^=(const int value);
    bool operator>(const bool value)const;
    bool operator<(const bool value)const;
    bool operator>=(const bool value)const;
    bool operator<=(const bool value)const;
};

#endif //CLION_BOOLVECTOR_H
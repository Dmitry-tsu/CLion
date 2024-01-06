#ifndef CLION_BOOLVECTOR_H
#define CLION_BOOLVECTOR_H
#include <cstdint>

class BoolVector
{
public:
    using SizeType = unsigned int;
    using Byte = unsigned char;
    const uint8_t cellSize = 8;

    BoolVector();
    explicit BoolVector(const char* data);
    BoolVector(const BoolVector& other);
    explicit BoolVector(SizeType length, bool value = false);
    ~BoolVector();
    void printCell(const int& cellNumber) const;
    void print() const;
    static int lenght();
    void set1(const int& cell, const int& pos)const;
    void set0(const int& cell, const int& pos)const;
    void swap(BoolVector& other);

private:
    SizeType length = 0;
    SizeType cellCount = 0;
    uint8_t insignificantPart = 0;
    Byte *data = nullptr;
};

#endif //CLION_BOOLVECTOR_H

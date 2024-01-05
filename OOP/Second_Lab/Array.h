#pragma once
class Array
{
public:
    Array(const int size = 10, const int value = 0);
    ~Array();
    void Print() const;
    int &operator[](const int index);
    //
    Array(const Array &other);
    int size() const;
    const int &operator[](const int index) const;
    //
    void RandArray(int FirstGap, int LastGap)const;
    void RandArrayIns(int FirstGap, int LastGap)const;
    void RandArrayDes(int FirstGap, int LastGap)const;
    void Swap(Array& other);
    Array &operator=(const Array & other);
    Array operator+(const Array& other) const;
    Array &operator+=(const Array& other);

private:
    int* m_array = nullptr;
    int m_size = 0;
};




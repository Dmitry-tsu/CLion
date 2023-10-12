#pragma once

#include<iostream>

class Array
{
public:
    Array(const int size = 10, const int value = 0);
    Array(const Array& other);
    ~Array();

    void Print() const;

    const int& operator[](const int index) const;
    int& operator[](const int index);

    int size() const;

    Array& operator=(const Array& other);
    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);
    void swap(Array& other);
    void resize(int size);
    int find(const int value) const;
    bool insert(const int index, const int value);

private:
    int* m_array = nullptr;
    int m_size = 0;
    void ensureCapacity(int capacity); // Вспомогательный метод для изменения ёмкости массива

};

std::ostream& operator<<(std::ostream& stream, const Array& arr);
std::istream& operator>>(std::istream& stream, Array& arr);


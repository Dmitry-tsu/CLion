#include<iostream>
#pragma once
class Array
{
public:

    class Iterator;

public:
    Array(Array&& other);
    Array(const int size = 10, const int value = 0);
    ~Array();
    void Print() const;
    int &operator[](const int index);
    Array(const Array &other);
    int Size() const;
    const int &operator[](const int index) const;
    void RandArray(int FirstGap, int LastGap)const;
    void RandArrayIns(int FirstGap, int LastGap)const;
    void RandArrayDes(int FirstGap, int LastGap)const;
    void Swap(Array& other);
    Array &operator=(const Array & other);
    Array operator+(const Array& other) const;
    Array &operator+=(const Array& other);
    Array &operator=( Array&& other);
    void Resize(int size);
    int ISearch(const int &el, int i=0) const;
    void Sort();
    bool Insert(const int &e, const int &in);
    bool DeleteByIndex(const int& in);
    bool DeleteElement(const int& el);
    bool DeleteAllElements(const int& el);
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;
    int IMax();
    int IMin();
    Array operator+(const int& item);
    Array operator+=(const int& item);

    Iterator begin();
    Iterator end();
    bool Insert(const int& el, Iterator &it);
    bool Remove(Iterator& gap1, Iterator& gap2);
    bool Remove(Iterator& it);

private:
    int* m_array = nullptr;
    int m_size = 0;
};

class Array::Iterator
{
public:
    Iterator(Array* array, const int pos);

    int& operator*();
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    bool hasNext() const;
    int Pos() const;
    void Repos(int index);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

private:
    Array* m_array = nullptr;
    int m_pos = 0;
};


std::ostream& operator<<(std::ostream& stream, const Array& arr);
std::istream& operator>>(std::istream& stream, const Array& arr);


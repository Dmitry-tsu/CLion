#pragma once
#include<iostream>
#include <algorithm>
#include <cassert>

template<typename ItemType>
class Array
{
public:

    template <typename IT, typename AT>
    class TemplateIterator;
    using Iterator = TemplateIterator<ItemType, Array>;
    using ConstIterator = TemplateIterator<const ItemType, const Array>;
    Array(const int size = 10, const ItemType &value = ItemType());
    Array(const Array &other);
    Array(Array&& other);
    ~Array();
    int Size() const;
    void Print() const;
    ItemType&operator[](const int index);
    const ItemType&operator[](const int index) const;
    Array& operator= ( Array&& other);
    Array& operator = (const Array & other);
    void RandArray(int FirstGap, int LastGap)const;
    void RandArrayIns(int FirstGap, int LastGap)const;
    void RandArrayDes(int FirstGap, int LastGap)const;
    void Swap(Array& other);
    Array operator+(const Array& other) const;
    Array &operator+=(const Array& other);
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;
    Array operator+(const ItemType& item);
    Array operator+=(const ItemType& item);
    void Resize(int size);
    int ISearch(const ItemType&el, int i=0)const;
    void Sort();
    bool Insert(const ItemType&e, const int &in);
    bool DelbyIndex(const int& in);
    bool DelElement(const ItemType& el);
    bool DelElementAll(const ItemType& el);
    int IMax();
    int IMin();

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    bool Insert(const ItemType& el, Iterator &it);
    bool Remove(const Iterator gap1, Iterator &gap2);
    bool Remove(const Iterator it);

private:
    ItemType* m_array = nullptr;
    int m_size = 0;
};
template <typename ItemType>
template <typename IT, typename AT>
class Array<ItemType>::TemplateIterator
{
public:
    TemplateIterator(AT* array = nullptr, const int pos = 0);
    IT& operator*();
    IT& operator[](const int offset);

    TemplateIterator& operator++();
    TemplateIterator operator++(int);
    TemplateIterator& operator--();
    TemplateIterator operator--(int);

    bool hasNext() const;
    int Pos() const;
    bool operator==(const TemplateIterator& other) const;
    bool operator!=(const TemplateIterator & other) const;

private:
    AT* m_array;
    int m_pos = -1;
};





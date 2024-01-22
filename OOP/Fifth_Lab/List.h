#ifndef IS_TEMPLATE_LIST_DECLARED
#define IS_TEMPLATE_LIST_DECLARED

#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>


template<typename ItemType>
class List
{
    using SizeType = unsigned int;
public:
    class Node;

    void FormHeadTail();
    void DeleteHeadTail();

    List(const List& other);
    List(SizeType size = 0, const ItemType value = ItemType());
    ~List();

    void PushFront(const ItemType& value);
    void PopFront();
    void PushBack(const ItemType &value);
    void PopBack();

    void Print() const;
    SizeType ReturnSize() const;
    void Swap(List &other);
    void Clear();
    bool isEmpty() const;
    void Insert(const int position, const ItemType& value);
    void Remove(const int position);
    ItemType Max() const;
    ItemType Min() const;

    //Node* Search(const ItemType& key) const;

    ItemType &operator[](const SizeType index);
    const ItemType &operator[](const SizeType index) const;
    bool operator==(const List &other) const;
    bool operator!=(const List &other) const;
    List& operator=(List &&other);
    List& operator=(const List &other);
    List operator+(const List& other) const;
    List& operator+=(const List& other);


private:

    SizeType m_size{};
    Node* m_head;
    Node* m_tail;
};

template <typename ItemType>
std::ostream& operator<<(std::ostream &stream, const List<ItemType> &list);
template <typename ItemType>
std::istream& operator >> (std::istream &stream, List<ItemType> &list);

template<typename ItemType>
class List<ItemType>::Node
{
public:
    friend class List;
private:
    Node(const ItemType& data)
            :data(data)
    {}

    ItemType data = ItemType();
    Node* prev = nullptr;
    Node* next = nullptr;
};

#include "List.cpp"
#endif



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
    List(const List& other);
    List(SizeType size=0, const ItemType value = ItemType());
    ~List();

    void PushBack(const ItemType &value);
    void Print();

private:

    SizeType m_size{};
    Node* m_head;
    Node* m_tail;
};


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



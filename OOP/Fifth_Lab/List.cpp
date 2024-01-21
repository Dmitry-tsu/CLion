#ifndef ARE_TEMPLATE_LIST_METHODS_DEFINED
#define ARE_TEMPLATE_LIST_METHODS_DEFINED

#include "List.h"
#include<iostream>

template <typename ItemType>
void List<ItemType>::FormHeadTail()
{
    m_head = new Node(ItemType());
    m_tail = new Node(ItemType());
    m_head->next = m_tail;
    m_tail->prev = m_head;
}

template <typename ItemType>
List<ItemType>::List(const List& other)
        :m_size(other.m_size)
{
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_size = other.m_size;
    Node* current = m_head->next;
    while (current != m_tail)
    {
        Node* new_node = new Node(current->data);
        new_node->next = current->next;
        new_node->prev = current->prev;
        current = current->next;
    }
}


template <typename ItemType>
List<ItemType>::List(SizeType size, const ItemType value)
{
    FormHeadTail();

    for (int i = 0; i < size; i++)
        PushBack(value);
}

template <typename ItemType>
List<ItemType>::~List()
{
    Node* current = m_head;
    while (current != nullptr)
    {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
}

template <typename ItemType>
void List<ItemType> ::PushBack(const ItemType& value)
{
    Node* new_node = new Node(value);
    new_node->prev = m_tail->prev;
    new_node->next = m_tail;
    m_tail->prev->next = new_node;
    m_tail->prev = new_node;
    m_size++;
}

template<typename ItemType>
void List<ItemType>::Print()
{
    if (m_head->next == m_tail)
        return;
    Node* current = m_head->next;
    std::cout << "[ ";
    while (current != m_tail->prev)
    {
        std::cout<< current->data << ", ";
        current = current->next;
    }
    std::cout << current->data << " ]";
    std::cout << std::endl;
}

#endif

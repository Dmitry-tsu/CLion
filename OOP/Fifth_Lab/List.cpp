#ifndef ARE_TEMPLATE_LIST_METHODS_DEFINED
#define ARE_TEMPLATE_LIST_METHODS_DEFINED

#include "List.h"
#include<iostream>

using SizeType = unsigned int;

template <typename ItemType>
void List<ItemType>::FormHeadTail()
{
    m_head = new Node(ItemType());
    m_tail = new Node(ItemType());
    m_head->next = m_tail;
    m_tail->prev = m_head;
}

template <typename ItemType>
void List<ItemType>::DeleteHeadTail()
{
    delete m_head;
    delete m_tail;
}

template <typename ItemType>
List<ItemType>::List(const List &other)
{
    FormHeadTail();
    Node* current = other.m_head->next;
    while (current != other.m_tail)
    {
        PushBack(current->data);
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
    Node* current = m_head->next;
    while (current != m_tail)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    DeleteHeadTail();
}

template <typename ItemType>
void List<ItemType> ::PushFront(const ItemType &value)
{
    Node* newNode = new Node(value);
    newNode->prev = m_head;
    newNode->next= m_head->next;
    m_head->next = newNode;
    newNode->next->prev = newNode;
    m_size++;
}

template <typename ItemType>
void List<ItemType> ::PopFront()
{
    Node* deleteNode = m_head->next;
    deleteNode->next->prev = m_head;
    m_head->next = deleteNode->next;
    m_size--;
    delete deleteNode;
}

template <typename ItemType>
void List<ItemType> ::PushBack(const ItemType &value)
{
    Node* new_node = new Node(value);
    new_node->prev = m_tail->prev;
    new_node->next = m_tail;
    m_tail->prev->next = new_node;
    m_tail->prev = new_node;
    m_size++;
}

template <typename ItemType>
void List<ItemType> ::PopBack()
{
    Node *deleteNode = m_tail->prev;
    deleteNode->prev->next = m_tail;
    m_tail->prev = deleteNode->prev;
    m_size--;
    delete deleteNode;
}

template<typename ItemType>
void List<ItemType>::Print() const
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


template<typename ItemType>
SizeType List<ItemType>::ReturnSize() const
{
    return m_size;
}

template<typename ItemType>
void List<ItemType>::Swap(List &other)
{
    std::swap(m_head, other.m_head);
    std::swap(m_size, other.m_size);
    std::swap(m_tail, other.m_tail);
}


#endif

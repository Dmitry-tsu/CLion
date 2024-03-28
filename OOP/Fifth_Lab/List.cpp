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
    Clear();
    DeleteHeadTail();
}

template <typename ItemType>
List<ItemType>::List(const Array<ItemType> &arr)
{
    FormHeadTail();
    for (int i = 0; i < arr.Size(); i++)
        PushBack(arr[i]);
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
    if (m_size > 0)
    {
        Node* deleteNode = m_head->next;
        deleteNode -> next -> prev = m_head;
        m_head->next = deleteNode->next;
        m_size--;
        delete deleteNode;
    }
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
void List<ItemType>::PopBack()
{
    if (m_size > 0)
    {
        Node *deleteNode = m_tail -> prev;
        deleteNode -> prev -> next = m_tail;
        m_tail -> prev = deleteNode -> prev;
        m_size--;
        delete deleteNode;
    }
}

template<typename ItemType>
void List<ItemType>::Print() const
{
    if (isEmpty())
    {
        std::cout << "[ ]\n";
        return;
    }
    Node *current = m_head->next;
    std::cout << "[ ";
    while (current != m_tail->prev)
    {
        std::cout << current->data << ", ";
        current = current -> next;
    }
    std::cout << current -> data << " ]";
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

template<typename ItemType>
void List<ItemType>::Clear()
{
    while (!isEmpty())
        PopBack();
}

template<typename ItemType>
bool List<ItemType>::isEmpty() const
{
    if (m_head->next == m_tail)
        return true;
    return false;
}

template<typename ItemType>
void  List<ItemType>::Insert(const int position, const ItemType &value)
{
    assert(m_size >= position && position >= 0);
    Insert(begin() + position, value);
}

template<typename ItemType>
void  List<ItemType>::Insert(const Iterator& it, const ItemType &value)
{
    assert(it!=nullptr);
    Node* newNode = new Node(value);
    newNode->prev = it.m_node->prev;
    newNode->next = it.m_node;
    it.m_node->prev->next = newNode;
    it.m_node->prev = newNode;
    m_size++;
}

template<typename ItemType>
void  List<ItemType>::InsertAfter(const ItemType &key, const ItemType &value)
{
    Iterator it = Search(key);
    Insert(++it, value);
}

template<typename ItemType>
void  List<ItemType>::Remove(const int position)
{
    assert(m_size >= position && position >= 0);
    Remove(begin() + position);
}

template<typename ItemType>typename
List<ItemType>::Iterator List<ItemType>::Remove(Iterator it)
{
    assert(!isEmpty());
    Node* deleteNode = it.m_node;
    ++it;
    deleteNode->prev->next = it.m_node;
    it.m_node->prev = deleteNode->prev;
    m_size--;
    delete deleteNode;
    return it;
}

template<typename ItemType>
bool  List<ItemType>::RemoveKey(const ItemType &key)
{
    Iterator it = Search(key);
    if (it == nullptr)
        return false;
    Remove(it);
    return true;
}

template<typename ItemType>
void  List<ItemType>::RemoveRange(Iterator first, Iterator last)
{

    while (first != last)
        first= Remove(first);

    Remove(last);
}

template<typename ItemType>
ItemType  List<ItemType>::Max() const
{
    if (m_size <= 0)
        return ItemType();
    ConstIterator max = begin();
    for (ConstIterator i = begin(); i != end(); ++i)
        if (*i > *max)
            max = i;
    return *max;
}


template<typename ItemType>
ItemType  List<ItemType>::Min() const
{
    if (m_size <= 0)
        return ItemType();
    ConstIterator min = begin();
    for (ConstIterator i = begin(); i != end(); ++i)
        if (*i < *min)
            min = i;
    return *min;
}

template<typename ItemType>typename
List<ItemType>::Iterator List<ItemType>::Search(const ItemType &key)
{
    Iterator it = begin();
    while (it != end())
    {
        if (*it == key)
            return  it;
        ++it;
    }
    return nullptr;

}

template<typename ItemType>typename
List<ItemType>::ConstIterator  List<ItemType>::Search(const ItemType &key) const
{
    ConstIterator  it = begin();
    while (it != end())
    {
        if (*it == key)
            return  it;
        ++it;
    }
    return nullptr;
}

template <typename ItemType>
void List<ItemType>::Sort()
{
    if (isEmpty())
        return;
    for (Iterator i = position(1); i != end(); ++i)
    {
        Iterator  j = i-1;
        while (*j > *i)
        {
            Iterator k = j + 1;
            SwapNode(k, j);
            --j;
            if (j == begin())
                break;
            --j;
        }
    }
}

template<typename ItemType>
ItemType &List<ItemType>::operator[](const SizeType index)
{
    assert(index < m_size);
    int i = 0;
    Node *current = m_head->next;
    while (i != index)
    {
        current = current->next;
        i++;
    }
    return current->data;
}

template<typename ItemType>
const ItemType &List<ItemType>::operator[](const SizeType index) const
{
    assert(index < m_size);
    int i = 0;
    Node* current = m_head->next;
    while (i != index)
    {
        current = current->next;
        i++;
    }
    return current->data;
}

template<typename ItemType>
bool List<ItemType>::operator==(const List &other) const
{
    if (m_size != other.m_size)
        return false;
    for (int i = 0; i < m_size; i++)
        if ((*this)[i] != other[i])
            return false;

    return true;
}

template<typename ItemType>
bool List<ItemType>::operator!=(const List &other) const
{
    if (*this == other)
        return false;

    return true;
}

template<typename ItemType>
List<ItemType> &List<ItemType>::operator=(List &&other)
{
    Swap(other);
    return *this;
}

template<typename ItemType>
List<ItemType> &List<ItemType>::operator=(const List &other)
{
    if (*this == other) return *this;
    while (m_size > other.m_size)
        PopBack();
    auto iter = other.begin();
    Node* current = m_head->next;
    for (int i = 0; i < m_size; i++)
    {
        current->data = *iter;
        current = current->next;
        ++iter;
    }
    while (m_size < other.m_size)
    {
        PushBack(*iter);
        ++iter;
    }
    return *this;
}

template <typename ItemType>
List<ItemType> List<ItemType>::operator+(const List &other) const
{
    List tmp(*this);
    tmp += other;
    return tmp;
}

template <typename ItemType>
List<ItemType> &List<ItemType>::operator+=(const List &other)
{
    for (const ItemType& item : other)
        PushBack(item);
    return *this;
}


template <typename ItemType>
std::ostream &operator<<(std::ostream &stream, const List<ItemType> &list)
{
    if (list.isEmpty())
    {
        stream << "[ ]";
        return stream;
    }
    stream << "[ ";
    for (int i = 0; i < list.Size()-1; i++)
        stream << list[i] << ", ";
    stream << list[list.Size() - 1] << " ]\n";
    return stream;
}

template <typename ItemType>
std::istream &operator >> (std::istream &stream, List<ItemType> &list)
{
    for (int i = 0; i < list.ReturnSize(); i++)
        stream >> list[i];

    return stream;
}

template <typename ItemType>
template <typename IT>
List<ItemType>::TemplateIterator<IT>::TemplateIterator(Node* node)
        : m_node(node)
{}

template <typename ItemType>
template <typename IT>
IT& List<ItemType>::TemplateIterator<IT>::operator*()
{
    assert(m_node != nullptr);
    return m_node->data;
}

template <typename ItemType>
template <typename IT>
const IT& List<ItemType>::TemplateIterator<IT>::operator*()const
{
    assert(m_node != nullptr);
    return m_node->data;
}

template <typename ItemType> typename
List<ItemType>::Iterator List<ItemType>::begin()
{
    return Iterator(m_head->next);
}

template <typename ItemType> typename
List<ItemType>::Iterator List<ItemType>::end()
{
    return Iterator(m_tail);
}

template <typename ItemType> typename
List<ItemType>::ConstIterator List<ItemType>::begin() const
{
    return ConstIterator(m_head->next);
}

template <typename ItemType> typename
List<ItemType>::ConstIterator List<ItemType>::end() const
{
    return ConstIterator(m_tail);
}

template <typename ItemType> typename
List<ItemType>::Iterator List<ItemType>::position(const int index)
{
    Iterator it = begin();
    for (int i = 0; i < index; ++i, ++it);
    return it;
}

template <typename ItemType> typename
List<ItemType>::ConstIterator List<ItemType>::position(const int index) const
{
    ConstIterator it = begin();
    for (int i = 0; i < index; ++i, ++it);
    return it;
}

template <typename ItemType>
template <typename IT>
typename List<ItemType>::template TemplateIterator<IT>& List<ItemType>::TemplateIterator<IT>::operator++()
{
    if (m_node != nullptr)
    {
        m_node = m_node->next;
    }
    return *this;
}

template <typename ItemType>
template <typename IT>
typename List<ItemType>::template TemplateIterator<IT>& List<ItemType>::TemplateIterator<IT>::operator--()
{
    if (m_node != nullptr)
    {
        m_node = m_node->prev;
    }
    return *this;
}

template <typename ItemType>
template <typename IT>
typename List<ItemType>::template TemplateIterator<IT> List<ItemType>::TemplateIterator<IT>::operator++(int)
{
    TemplateIterator old(m_node);
    ++(*this);
    return old;
}

template <typename ItemType>
template <typename IT>
typename List<ItemType>::template TemplateIterator<IT> List<ItemType>::TemplateIterator<IT>::operator--(int)
{
    TemplateIterator old(m_node);
    --(*this);
    return old;
}


template <typename ItemType>
template <typename IT>
bool List<ItemType>::TemplateIterator<IT>::operator==(const TemplateIterator& other) const
{
    return m_node == other.m_node;
}


template <typename ItemType>
template <typename IT>
bool List<ItemType>::TemplateIterator<IT>::operator!=(const TemplateIterator& other) const
{
    return !(*this == other);
}

template <typename ItemType>
template <typename IT>
typename List<ItemType>::template TemplateIterator<IT> List<ItemType>::TemplateIterator<IT>::operator+(const int& index)
{
    TemplateIterator result(m_node);
    for (int i = 0; i < index; ++i)
    {
        ++result;
    }
    return result;
}

template <typename ItemType>
template <typename IT>
typename List<ItemType>::template TemplateIterator<IT> List<ItemType>::TemplateIterator<IT>::operator-(const int& index)
{
    TemplateIterator result(m_node);
    for (int i = 0; i < index; ++i) {
        --result;
    }
    return result;
}

////////////
template<typename ItemType>
void List<ItemType>::TakeNode(Iterator &it)
{
    assert(!isEmpty());

    Node* current = it.m_node->next;

    it.m_node->prev->next = current;
    current->prev = it.m_node->prev;
    m_size--;
}

template<typename ItemType>
void List<ItemType>::InsertNode(Iterator &current, const Iterator &other)
{

    current.m_node->prev = other.m_node->prev;
    current.m_node->next = other.m_node;

    other.m_node->prev->next = current.m_node;
    other.m_node->prev = current.m_node;
    m_size++;
}

template<typename ItemType>
void List<ItemType>::SwapNode(Iterator &one, Iterator &two)
{
    int pos_one = PosNode(one);
    int pos_two = PosNode(two);
    TakeNode(one);
    TakeNode(two);
    InsertNode(one, (begin() + pos_two));
    InsertNode(two, (begin() + pos_one));

}

template<typename ItemType>
int List<ItemType>::PosNode(Iterator &current)
{
    if (isEmpty())
        return -1;
    int count = 0;
    Iterator it = begin();
    while (it != current)
    {
        ++count;
        ++it;
    }
    return count;
}

#endif
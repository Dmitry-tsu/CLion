#ifndef IS_TEMPLATE_LIST_DECLARED
#define IS_TEMPLATE_LIST_DECLARED

#include <iostream>
#include <algorithm>
#include <cassert>
#include "../../CLion/OOP/Second_Lab/Array.h"

template<typename ItemType>
class List
{
    using SizeType = unsigned int;
public:
    class Node;

    template <typename IT>
    class TemplateIterator;
    using Iterator = TemplateIterator<ItemType>;
    using ConstIterator = TemplateIterator<const ItemType>;

    void FormHeadTail();
    void DeleteHeadTail();

    List(const List &other);
    List(SizeType size = 0, const ItemType value = ItemType());
    ~List();
    List(const Array<ItemType> &arr);


    void PushFront(const ItemType& value);
    void PopFront();
    void PushBack(const ItemType &value);
    void PopBack();

    void Print() const;
    SizeType ReturnSize() const;
    void Swap(List &other);
    void Clear();
    bool isEmpty() const;
    void Insert(const int position, const ItemType &value);
    void Insert(const Iterator &it, const ItemType &value);
    void InsertAfter(const ItemType &key, const ItemType &value);
    void Remove(const int position);
    Iterator Remove(Iterator it);
    bool RemoveKey(const ItemType &key);
    void RemoveRange(Iterator first, Iterator last);
    ItemType Max() const;
    ItemType Min() const;

    Iterator Search(const ItemType &key);
    ConstIterator Search(const ItemType &key) const;
    void Sort();

    ItemType &operator[](const SizeType index);
    const ItemType &operator[](const SizeType index) const;
    bool operator==(const List &other) const;
    bool operator!=(const List &other) const;
    List &operator=(List &&other);
    List &operator=(const List &other);
    List operator+(const List &other) const;
    List &operator+=(const List &other);

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator position(const int index);
    ConstIterator position(const int index) const;
private:

    SizeType m_size{};
    Node  *m_head;
    Node *m_tail;
    void TakeNode(Iterator &it);
    void InsertNode(Iterator &current, const Iterator &other);
    void SwapNode(Iterator &current, Iterator &other);
    int PosNode(Iterator &current);
};

template <typename ItemType>
std::ostream &operator<<(std::ostream &stream, const List<ItemType> &list);
template <typename ItemType>
std::istream &operator >> (std::istream &stream, List<ItemType> &list);

template<typename ItemType>
class List<ItemType>::Node
{
public:
    friend class List;
private:
    Node(const ItemType &data)
            :data(data)
    {}

    ItemType data = ItemType();
    Node* prev = nullptr;
    Node* next = nullptr;
};

template <typename ItemType>
template <typename IT>
class List<ItemType>::TemplateIterator
{
public:

    friend class List;
    TemplateIterator(Node *node = nullptr);
    IT &operator*();
    const IT& operator*() const;
    TemplateIterator &operator++();
    TemplateIterator &operator--();

    // исправлено
    TemplateIterator operator++(int);
    TemplateIterator operator--(int);
    TemplateIterator operator+(const int &index);
    TemplateIterator operator-(const int &index);


    bool operator == (const TemplateIterator &other) const;
    bool operator != (const TemplateIterator &other) const;

private:
    Node* m_node = nullptr;
    //Node* m_head = nullptr;
    //Node* m_tail = nullptr;
};




#include "List.cpp"
#endif


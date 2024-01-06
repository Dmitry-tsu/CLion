
//#pragma once
#ifndef ARRAY_TEMPLATE
#define ARRAY_TEMPLATE
#include<iostream>
#include <algorithm>
#include <assert.h>

template<typename ItemType>
class Array
{
public:

    template <typename IT, typename AT>
    class TemplateIterator;
    using Iterator = TemplateIterator<ItemType, Array>;
    using ConstIterator = TemplateIterator<const ItemType, const Array>;
public:

    Array(Array&& other);
    Array(const int size = 10, const ItemType &value = ItemType());
    ~Array();
    void Print() const;
    Array(const Array &other);
    int Size() const;
    ItemType&operator[](const int index);
    const ItemType&operator[](const int index) const;
    void RandArray(int FirstGap, int LastGap)const;
    void RandArrayIns(int FirstGap, int LastGap)const;
    void RandArrayDes(int FirstGap, int LastGap)const;
    void Swap(Array& other);
    Array &operator=(const Array & other);
    Array operator+(const Array& other) const;
    Array &operator+=(const Array& other);
    Array &operator=( Array&& other);
    void Resize(int size);
    int ISearch(const ItemType&el, int i=0)const;
    void Sort();
    bool Insert(const ItemType&e, const int &in);
    bool DeleteByIndex(const int& in);
    bool DeleteElement(const ItemType& el);
    bool DeleteAllElements(const ItemType& el);
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;
    int IMax();
    int IMin();
    Array operator+(const ItemType& item);
    Array operator+=(const ItemType& item);

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    bool Insert(const ItemType& el, const Iterator &it);
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
    TemplateIterator operator+(const int& index);
    TemplateIterator operator-(const int& index);

    bool hasNext() const;
    int Pos() const;
    bool operator==(const TemplateIterator& other) const;
    bool operator!=(const TemplateIterator & other) const;

private:
    AT* m_array;
    int m_pos = -1;
};


template <typename ItemType>
Array<ItemType>::Array(const int size, const ItemType& value)
{
    if (size < 0)
    {
        std::cerr << "Array::Array: size is negative, invert.";
        m_size = -size;
    }
    else m_size = size;
    m_array = new ItemType[m_size];

    for (int i = 0; i < m_size; i++)
        m_array[i] = value;
}

template <typename ItemType>
Array<ItemType>::Array(const Array& other)
        :m_size(other.m_size)
{
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++)
        m_array[i] = other.m_array[i];
}

template <typename ItemType>
Array<ItemType>::Array(Array&& other)
{
    Swap(other);
}

template <typename ItemType>
Array<ItemType>::~Array()
{
    delete[] m_array;
}

template <typename ItemType>
int Array<ItemType>::Size() const
{
    return m_size;
}

template <typename ItemType>
void Array<ItemType>::Print() const
{
    int i = 0;
    //int a = *this[i];
    std::cout << *this;

    /*std::cout << "[";
    for (int i = 0; i < m_size - 1; i++)
        std::cout << m_array[i] << ",";

    std::cout << m_array[m_size - 1] << "]\n";*/

}

template <typename ItemType>
ItemType& Array<ItemType>::operator[](const int index)
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
const ItemType& Array<ItemType>::operator[](const int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator= (Array&& other)
{

    /*
     //������������ ���������� ����� copy-and-swap idiom
     //�������� �������� ������ ���� ������� �������� ����������( ������ �� ����� �������)
      Array &Array::operator=(Array other)
      {
        Swap(other);
        return *this;
      }
    */
    Swap(other);
    return *this;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator= (const Array& other)
{
    if (this == &other) return *this;

    if (m_size != other.m_size)
    {
        m_size = other.m_size;
        delete[]m_array;
        m_array = new ItemType[m_size];
    }
    for (int i = 0; i < m_size; i++)
        m_array[i] = other.m_array[i];

    return *this;

}

template <> inline
void Array<int>::RandArray(int f_gap, int l_gap)const
{
    if (f_gap > l_gap)
    {
        int swap = f_gap; f_gap = l_gap; l_gap = swap;
    }
    srand(time(0));
    for (int i = 0; i < m_size; i++) m_array[i] = rand() % l_gap + f_gap + 1;
}

template <> inline
void Array<int>::RandArrayIns(int f_gap, int l_gap)const
{
    if (f_gap > l_gap) std::swap(f_gap, l_gap);
    srand(time(0));
    m_array[0] = rand() % l_gap + f_gap + 1; // ������ ����� �������� ��������
    int i;
    for (i = 1; i < m_size; i++)
    {
        m_array[i] = m_array[i - 1] + rand() % 10 + 1;
        if (m_array[i] > l_gap) break;
    }
    for (; i < m_size; i++)
        m_array[i] = l_gap;

}

template <> inline
void Array<int>::RandArrayDes(int f_gap, int l_gap)const
{
    if (f_gap > l_gap) std::swap(f_gap, l_gap);
    srand(time(0));
    m_array[m_size - 1] = rand() % l_gap + f_gap + 1; // ������ ����� �������� ��������
    int i;
    for (i = m_size - 2; i >= 0; i--)
    {
        m_array[i] = m_array[i + 1] + rand() % 10 + 1;
        if (m_array[i] < f_gap) break;
    }
    for (; i >= 0; i--)
        m_array[i] = f_gap;
}

template <typename ItemType>
void Array<ItemType>::Swap(Array& other)
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array& other) const
{
    Array res(m_size + other.m_size);
    for (int i = 0; i < m_size; i++)
        res.m_array[i] = m_array[i];
    for (int i = 0; i < other.m_size; i++)
        res.m_array[m_size + i] = other.m_array[i];
    return res;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const Array& other)
{
    Array tmp(*this + other);
    this->Swap(tmp);
    return *this;
}

template <typename ItemType>
bool Array<ItemType>::operator==(const Array& other) const
{
    if (m_size != other.m_size) return false;
    for (int i = 0; i < m_size; i++)
        if (m_array[i] != other.m_array[i]) return false;
    return true;
}

template <typename ItemType>
bool Array<ItemType>::operator!=(const Array& other) const
{
    if (*this == other) return false;
    return true;
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const ItemType& item)
{
    Array arr(1, item);
    return *this + arr;
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+=(const ItemType& item)
{
    Array arr(1, item);
    return *this += arr;;
}

template <typename ItemType>
std::ostream& operator<<(std::ostream& stream, const Array<ItemType>& arr)
{
    if (arr.Size() == 0)
        return stream << "[]";
    stream << "[";
    for (int i = 0; i < arr.Size() - 1; i++)
        stream << arr[i] << ",";

    stream << arr[arr.Size() - 1] << "]\n";
    return stream;
}

template <typename ItemType>
std::istream& operator >> (std::istream& stream,  Array<ItemType>& arr)
{
    for (int i = 0; i < arr.Size(); i++)
        stream >> arr[i];

    return stream;
}

template <typename ItemType>
void Array<ItemType>::Resize(int size)
{
    if (size < 0)
    {
        std::cerr << "Array::rersize: size is negative, inveert...\n";
        size = -size;
    }
    Array res(size);
    int count = std::min(m_size, size);
    for (int i = 0; i < count; i++)
        res.m_array[i] = m_array[i];
    res.Swap(*this);
}

template <typename ItemType>
int Array<ItemType>::ISearch(const ItemType& el, int i)const
{
    for (i; i < m_size; i++)
        if (m_array[i] == el) return i;
    return -1;
}

template <typename ItemType>
void Array<ItemType>::Sort()
{
    for (int i = 1; i < m_size; i++)
    {
        ItemType key = m_array[i];
        int j;
        for (j = i - 1; key < m_array[j] && j >= 0; j--) m_array[j + 1] = m_array[j];
        m_array[j + 1] = key;
    }
}

template <typename ItemType>
bool Array<ItemType>::Insert(const ItemType& e, const int& in)
{
    if (in > m_size) return false;
    Resize(m_size + 1);
    int i;
    for (i = m_size - 2; i >= in; i--)
        m_array[i + 1] = m_array[i];
    m_array[i + 1] = e;
    return true;

}

template <typename ItemType>
bool Array<ItemType>::DeleteByIndex(const int& in)
{
    if (in >= m_size) return false;
    int i;
    for (i = in; i <= m_size - 2;)
    {
        m_array[i] = m_array[i + 1];
        i++;
    }
    m_array[i] = ItemType(0);
    Array arr(m_size - 1);
    for (i = 0; i < arr.m_size; i++)
        arr.m_array[i] = m_array[i];
    *this = arr;
    return true;
}

template <typename ItemType>
bool Array<ItemType>::DeleteElement(const ItemType& el)
{
    int index = ISearch(el);
    if (index == -1) return false;
    return DeleteByIndex(index);
}

template <typename ItemType>
bool Array<ItemType>::DeleteAllElements(const ItemType& el)
{
    int index = ISearch(el);
    if (index == -1) return false;
    while (DeleteByIndex(index))
    {
        index = ISearch(el, index);
        if (index == -1) return false;
    }
    return true;
}

template <typename ItemType>
int Array<ItemType>::IMax()
{
    int i_max = -1, i;
    for (i = 0; i < m_size; i++)
    {
        if (i_max == -1) i_max = 0;
        if (m_array[i_max] < m_array[i]) i_max = i;
    }
    return i_max;
}

template <typename ItemType>
int Array<ItemType>::IMin()
{
    int i_min = -1, i;
    for (i = 0; i < m_size; i++)
    {
        if (i_min == -1) i_min = 0;
        if (m_array[i_min] > m_array[i]) i_min = i;
    }
    return i_min;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>::TemplateIterator(AT* array, const int pos)
        : m_array(array)
        , m_pos(pos)
{}

template <typename ItemType>
template <typename IT, typename AT>
IT& Array<ItemType>::TemplateIterator<IT, AT>::operator*()
{
    return m_array->operator[](m_pos);
}

template <typename ItemType>
template <typename IT, typename AT>
IT& Array<ItemType>::TemplateIterator<IT, AT>::operator[](const int offset)
{
    return *(operator+(offset));
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT>& Array<ItemType>::TemplateIterator<IT, AT>::operator++()
{
    ++m_pos;
    return *this;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator++(int)
{
    Array<ItemType>::TemplateIterator<IT, AT> old(*this);
    ++m_pos;
    return old;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> &Array<ItemType>::TemplateIterator<IT, AT>::operator--()
{
    --m_pos;
    return *this;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator--(int)
{
    Array<ItemType>::TemplateIterator<IT, AT> old(*this);
    --m_pos;
    return old;
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::hasNext() const
{
    return (m_pos < m_array->Size());
}

template <typename ItemType>
template <typename IT, typename AT>
int Array<ItemType>::TemplateIterator<IT, AT>::Pos() const
{
    return m_pos;
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::operator==(const TemplateIterator& other) const
{
    assert(m_array == other.m_array);
    return (m_array == other.m_array && m_pos == other.m_pos);
}

template <typename ItemType>
template <typename IT, typename AT>
bool Array<ItemType>::TemplateIterator<IT, AT>::operator!=(const TemplateIterator& other) const
{
    return !operator==(other);
}

template <typename ItemType> typename
Array<ItemType>::Iterator Array<ItemType>::begin()
{
    return Iterator(this, 0);
}

template <typename ItemType> typename
Array<ItemType>::Iterator Array<ItemType>::end()
{
    return Iterator(this, m_size);
}

template <typename ItemType> typename
Array<ItemType>::ConstIterator Array<ItemType>::begin() const
{
    return ConstIterator(this, 0);
}

template <typename ItemType> typename
Array<ItemType>::ConstIterator Array<ItemType>::end() const
{
    return ConstIterator(this, m_size);
}




template <typename ItemType>
bool Array<ItemType>::Insert(const ItemType& el, const Iterator& it)
{
    return Insert(el, it.Pos());
}

template <typename ItemType>
bool Array<ItemType>::Remove(const Iterator gap1, Iterator& gap2)
{
    if (gap1.Pos() > gap2.Pos() || gap1.Pos() < 0 || gap2.Pos() > m_size)
        return false;
    int numtorem = gap2.Pos() - gap1.Pos();
    int ishift = gap2.Pos();
    for (int i = gap1.Pos(); i < m_size - numtorem; i++)
    {
        m_array[i] = m_array[ishift];
        ishift++;
    }
    for (int i = 0; i < numtorem; i++, gap2--);
    Resize(m_size - numtorem);
    return true;
}

template <typename ItemType>
bool Array<ItemType>::Remove(const Iterator it)
{
    Iterator it2(this, it.Pos() + 1);
    return Remove(it, it2);
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator+(const int& index)
{

    Array<ItemType>::TemplateIterator<IT, AT> tmp(*this);
    for (int i = 0; i < index; ++i)
        ++tmp;

    return tmp;
}

template <typename ItemType>
template <typename IT, typename AT>
Array<ItemType>::TemplateIterator<IT, AT> Array<ItemType>::TemplateIterator<IT, AT>::operator-(const int& index)
{

    Array<ItemType>::TemplateIterator<IT, AT> tmp(*this);
    for (int i = 0; i < index; ++i)
        --tmp;

    return tmp;
}
#endif


#include "Array.h"
#include <iostream>
#include "assert.h"
Array::Array(const int size, const int value)
{
    if (size < 0)
    {
        std::cerr << "Array::Array: Size is negative, invert.";
        m_size = -size;
    }
    else m_size = size;
    m_array = new int[m_size];

    for (int i = 0; i < m_size; i++)
        m_array[i] = value;
}
Array::Array(const Array &other)
        :m_size(other.m_size)
{
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
        m_array[i] = other.m_array[i];
}


Array::~Array()
{
    delete[] m_array;
}

int Array::Size() const
{
    return m_size;
}
void Array::Print() const
{
    std::cout << *this;
}

int& Array::operator[](const int index)
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

const int& Array::operator[](const int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

Array&Array::operator=(const Array &other)
{
    if (this == &other) return *this;
    if (m_size != other.m_size) {
        m_size = other.m_size;
        delete[]m_array;
        m_array = new int[m_size];
    }
    for (int i = 0; i < m_size; i++)
        m_array[i] = other.m_array[i];
    return *this;
}

Array&Array::operator=(Array&& other)
{
    Swap(other);
    return *this;
}

void Array::RandArray( int f_gap, int l_gap)const
{
    if (f_gap > l_gap)
    {
        int swap = f_gap; f_gap = l_gap; l_gap = swap;
    }
    srand(time(nullptr));
    for (int i = 0; i < m_size; i++) m_array[i] = rand() % l_gap +f_gap+1;
}

void Array::RandArrayIns(int f_gap, int l_gap)const
{
    if (f_gap > l_gap) std::swap(f_gap, l_gap);
    srand(time(0));
    m_array[0] = rand() % l_gap + f_gap + 1;
    int i;
    for (i = 1; i < m_size; i++)
    {
        m_array[i] = m_array[i - 1] + rand() % 10 + 1;
        if (m_array[i] > l_gap) break;
    }
    for (; i < m_size; i++)
        m_array[i] = l_gap;

}

void Array::RandArrayDes(int f_gap, int l_gap)const
{
    if (f_gap > l_gap) std::swap(f_gap, l_gap);
    srand(time(0));
    m_array[m_size-1] = rand() % l_gap + f_gap + 1;
    int i;
    for (i = m_size-2; i >= 0; i--)
    {
        m_array[i] = m_array[i + 1] + rand() % 10 + 1;
        if (m_array[i] < f_gap) break;
    }
    for (; i >= 0; i--)
        m_array[i] = f_gap;
}

void Array::Swap(Array& other)
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}
Array Array::operator+(const Array& other) const
{
    Array res(m_size+other.m_size);
    for (int i = 0; i < m_size; i++)
        res.m_array[i] = m_array[i];
    for (int i = 0; i < other.m_size; i++)
        res.m_array[m_size+i] = other.m_array[i];
    return res;

}
Array &Array::operator+=(const Array& other)
{
    Array tmp(*this + other);
    this->Swap(tmp);
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Array& arr)
{
    stream << "[";
    for (int i = 0; i < arr.Size() - 1; i++)
        stream << arr[i] << ",";

    stream << arr[arr.Size() - 1] << "]\n";
    return stream;
}

std::istream& operator>>(std::istream& stream, const Array& arr)
{
    for (int i = 0; i < arr.Size(); i++)
        stream >> arr[i];

    return stream;
}

void Array::Resize(int size)
{
    if (size < 0)
    {
        std::cerr << "Array::resize: size is negative, invert...\n";
        size = -size;
    }
    Array res(size);
    int count = std::min(m_size, size);
    for (int i = 0; i < count; i++)
        res.m_array[i] = m_array[i];
    res.Swap(*this);
}

int Array::ISearch(const int &el, int i) const
{
    for (i; i < m_size; i++)
        if (m_array[i] == el) return i;
    return -1;
}

void Array::Sort()
{
    for (int i = 1; i < m_size; i++)
    {
        int key = m_array[i];
        int j;
        for (j = i - 1; key < m_array[j] && j >= 0; j--) m_array[j + 1] = m_array[j];
        m_array[j + 1] = key;
    }
}

bool Array::Insert(const int& e,const int& in)
{
    if (in >= m_size) return false;
    Resize(m_size + 1);
    int i;
    for (i = m_size-2; i >= in; i--)
        m_array[i + 1] = m_array[i];
    m_array[i + 1] = e;
    return true;
}

bool Array::DeleteByIndex(const int& in)
{
    if (in >= m_size) return false;
    int i;
    for (i = in; i <= m_size - 2;)
    {
        m_array[i] = m_array[i + 1];
        i++;
    }
    m_array[i] = 0;
    Array arr(m_size - 1);
    for (i = 0; i < arr.m_size; i++)
        arr.m_array[i] = m_array[i];
    *this=arr;
    return true;
}

bool Array::DeleteElement(const int& el)
{
    int index = ISearch(el);
    if (index == -1) return false;
    return DeleteByIndex(index);
}


bool Array::DeleteAllElements(const int& el)
{
    int index = ISearch(el);
    if (index == -1) return false;
    while (DeleteByIndex(index))
    {
        index = ISearch(el,index);
        if (index == -1) return false;
    }
    return true;
}

bool Array::operator==(const Array& other) const
{
    if (m_size != other.m_size) return false;
    for (int i = 0; i < m_size; i++)
        if (m_array[i] != other.m_array[i]) return false;
    return true;
}

bool Array::operator!=(const Array& other) const
{
    if (*this == other) return false;
    return true;
}

int Array::IMax()
{
    int i_max = -1,i;
    for (i = 0; i < m_size; i++)
    {
        if (i_max==-1) i_max = 0;
        if (m_array[i_max] < m_array[i]) i_max = i;
    }
    return i_max;
}

int Array::IMin()
{
    int i_min = -1, i;
    for (i = 0; i < m_size; i++)
    {
        if (i_min==-1) i_min = 0;
        if (m_array[i_min] > m_array[i]) i_min = i;
    }
    return i_min;
}


Array Array::operator+(const int& item)
{
    Array arr(1, item);
    return *this + arr;
}

Array Array::operator+=(const int& item)
{
    Array arr(1, item);
    return *this += arr;;
}

Array::Array(Array&& other)
{
    Swap(other);
}

Array::Iterator Array::begin()
{
    return Iterator(this, 0);
}

Array::Iterator Array::end()
{
    return Iterator(this, Size());
}

Array::Iterator::Iterator(Array* array, const int pos)
        : m_array(array)
        , m_pos(pos)
{}

int& Array::Iterator::operator*()
{
    return (*m_array)[m_pos];
}

Array::Iterator& Array::Iterator::operator++()
{
    ++m_pos;
    return *this;
}

Array::Iterator Array::Iterator::operator++(int)
{
    Iterator old(*this);
    ++m_pos;
    return old;
}

Array::Iterator& Array::Iterator::operator--()
{
    --m_pos;
    return *this;
}

Array::Iterator Array::Iterator::operator--(int)
{
    Iterator old(*this);
    --m_pos;
    return old;
}

bool Array::Iterator::hasNext() const
{
    return (m_pos < m_array->Size());
}

bool Array::Iterator::operator==(const Iterator& other) const
{
    assert(m_array == other.m_array);
    return (m_array == other.m_array && m_pos == other.m_pos);
}

bool Array::Iterator::operator!=(const Iterator& other) const
{
    return !operator==(other);
}

int Array::Iterator::Pos() const
{
    return m_pos;
}

bool Array::Insert(const int& el, Iterator &it)
{
    Array::Iterator i = end();
    if (i == it) return false;
    Resize(m_size + 1);
    for (; i != it; i--)
        *++i = *--i;
    *i = el;
    it++;
    return true;
}

bool Array::Remove(Iterator& gap1, Iterator& gap2)
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
    for (int i = 0; i < numtorem ; i++, gap2--);
    Resize(m_size - numtorem);
    return true;
}

bool Array::Remove(Iterator& it)
{
    Iterator it2(this, it.Pos() + 1);
    return Remove(it, it2);
}


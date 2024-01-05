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

std::istream& operator >> (std::istream& stream, const Array& arr)
{
    for (int i = 0; i < arr.Size() - 1; i++)
        stream >> arr[i];

    return stream;
}

void Array::Resize(int size)
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
}

int Array::ISearch(const int e) const
{
    for (int i = 0; i < m_size; i++)
        if (m_array[i] == e) return i;
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
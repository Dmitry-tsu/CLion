#include "Array.h"
#include <iostream>
#include <cassert>

Array::Array(const int size, const int value)
{
    if (size < 0)
    {
        std::cerr << "Array::Array: size is negative, invert...\n";
        m_size = -size;
    }
    else
    {
        m_size = size;
    }

    m_array = new int[m_size];

    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = value;
    }
}

Array::Array(const Array& other)
        : m_size(other.m_size)
{
    m_array = new int[m_size];

    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
}

Array::~Array()
{
    delete[] m_array;
}

void Array::Print() const
{
    std::cout << *this;
}

const int& Array::operator[](const int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

int& Array::operator[](const int index)
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

int Array::size() const
{
    return m_size;
}

Array& Array::operator=(const Array& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (m_size != other.m_size)
    {
        m_size = other.m_size;
        delete[] m_array;
        m_array = new int[m_size];
    }

    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }

    return *this;
}

Array Array::operator+(const Array& other) const
{
    Array result(m_size + other.m_size);

    for (int i = 0; i < m_size; ++i)
    {
        result.m_array[i] = m_array[i];
    }

    for (int i = 0; i < other.m_size; ++i)
    {
        result.m_array[m_size + i] = other.m_array[i];
    }

    return result;
}

void Array::swap(Array& other)
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

void Array::resize(int size)
{
    if (size < 0)
    {
        std::cerr << "Array::resize: size is negative, invert...\n";
        m_size = -size;
    }

    Array resized(size);
    int count = std::min(m_size, size);

    for (int i = 0; i < count; ++i)
    {
        resized.m_array[i] = m_array[i];
    }

    resized.swap(*this);
}

Array& Array::operator+=(const Array& other)
{
    Array tmp = *this + other;
    this->swap(tmp);
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Array& arr)
{
    stream << "[";

    for (int i = 0; i < arr.size() - 1; ++i)
    {
        stream << arr[i] << ", ";
    }

    stream << arr[arr.size() - 1] << "]";
    return stream;
}

std::istream& operator>>(std::istream& stream, Array& arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        stream >> arr[i];
    }
    return stream;
}



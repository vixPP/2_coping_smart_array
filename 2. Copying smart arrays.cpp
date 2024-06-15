#include <iostream>
#include <cstdlib>

class smart_array
{
public:
    smart_array(size_t size) : m_size(size), m_data(new int[size])
    {
        if (!m_data)
        {
            throw std::runtime_error("error");
        }
    }

    ~smart_array()
    {
        delete[] m_data;
    }

    smart_array& operator=(const smart_array& other)
    {
        if (this != &other)
        {
            delete[] m_data;
            m_size = other.m_size;
            m_current_size = other.m_current_size;
            m_data = new int[m_size];
            std::copy(other.m_data, other.m_data + other.m_current_size, m_data);
        }
        return *this;
    }

    smart_array(const smart_array& other) : m_size(other.m_size), m_current_size(other.m_current_size), m_data(new int[other.m_size])
    {
        std::copy(other.m_data, other.m_data + other.m_current_size, m_data);
    }

    void add_element(int value)
    {
        if (m_current_size < m_size)
        {
            m_data[m_current_size++] = value;
        }
        else
        {
            throw std::length_error("Array is full");
        }
    }

    int get_element(size_t index) const
    {
        if (index >= m_current_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

private:
    size_t m_size;
    size_t m_current_size = 0;
    int* m_data;
};

int main()
{
    try
    {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
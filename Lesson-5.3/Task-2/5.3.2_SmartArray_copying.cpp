#include <iostream>

class smart_array
{
public:
    smart_array(int initCapacity) : capacity(initCapacity), data(new int[initCapacity]) {
        size = 0;
    }
    smart_array(const smart_array& other) : capacity(other.capacity), data(new int[other.capacity]) {
        std::copy(other.data, other.data + capacity, data);
    }
    smart_array& operator = (const smart_array& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            data = new int[capacity];
            std::copy(other.data, other.data + capacity, data);
        }
        return *this;
    }
    ~smart_array() { delete[] data; }

    int get_element(int index) {
        if (index < 0 || index >= size) {
            throw std::runtime_error("Некорректный индекс!");
        }
        for (int i = 0; i < size; i++) { return data[index]; }
    }
    void add_element(int value) {
        size++;
        if (size > capacity) {
            throw std::runtime_error("За пределами массива!");
        }
        int ind = size - 1;
        data[ind] = value;
    }
private:
    int* data{ nullptr };
    int size; int capacity;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);

    arr = new_array;

    std::cout << arr.get_element(1) << std::endl;
    std::cout << new_array.get_element(1) << std::endl;
}

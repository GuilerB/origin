#include <iostream>

class smart_array
{
public:
    smart_array(int initCapacity) {
        data = new int[initCapacity]; 
        capacity = initCapacity;
        size = 0; 
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

    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        //arr.add_element(18724); // оставил для проверки

        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

}

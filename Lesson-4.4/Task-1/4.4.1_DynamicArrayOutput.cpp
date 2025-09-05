#include <iostream>

void print_dynamic_array(int* arr, int logical_size, int actual_size) {
    
    std::cout << "Динамический массив: ";
    for (int i = 0; i < actual_size; ++i) {
        if (i >= logical_size) { std::cout << "_ "; }
        else { std::cout << arr[i] << " "; }
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";
    
    while (true) {

        int actSize{ 0 }, logicSize{ 0 };
        std::cout << "Введите фактичеcкий размер массива: ";
        std::cin >> actSize;
        std::cout << "Введите логичеcкий размер массива: ";
        std::cin >> logicSize;   
       
        if (actSize < logicSize){
            std::cout << "Фактический размер не должен быть < логического!";
            std::cout << std::endl;
            continue;
        }

        int* dynamicArray = new int[actSize];

        for (int i = 0; i < logicSize; ++i) {
            std::cout << "Введите arr[" << i << "]: ";
            std::cin >> dynamicArray[i];
        }
        
        print_dynamic_array(dynamicArray, logicSize, actSize);
        
        delete[] dynamicArray;
        dynamicArray = nullptr; 
    }
}

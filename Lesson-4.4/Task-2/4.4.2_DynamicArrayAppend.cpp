#include <iostream>

int* append_to_dynamic_array(int* arr, int &logical_size, int &actual_size, int &elem) {

    if (actual_size == logical_size) {
        actual_size = actual_size * 2;
        logical_size = logical_size + 1;

        int* newDynamicArray = new int[actual_size];

        for (int i = 0; i < (logical_size-1); ++i) {
            newDynamicArray[i] = arr[i];
        }
        newDynamicArray[logical_size-1] = elem;

        delete[] arr;
        arr = newDynamicArray;

        return arr;
    }   
    else if (actual_size > logical_size) {
        logical_size += 1;
        arr[logical_size-1] = elem;
        return arr;
    }
}

void print_dynamic_array(int* arr, int &logical_size, int &actual_size) {

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

        if (actSize < logicSize) {
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
        
        while (true){
            int appElem{ 0 };
            std::cout << "Введите элемент для добавления: ";
            std::cin >> appElem;

            if (appElem == 0) {
                std::cout << "Спасибо! Ваш массив: ";
                for (int i = 0; i < actSize; ++i) {
                    if (i >= logicSize) { std::cout << "_ "; }
                    else { std::cout << dynamicArray[i] << " "; }
                };
                std::cout << "\n\n\n";
                break;
            }
            
            dynamicArray = append_to_dynamic_array(dynamicArray, logicSize, actSize, appElem);
 
            print_dynamic_array(dynamicArray, logicSize, actSize);           
        }

        delete[] dynamicArray;
        dynamicArray = nullptr;
    }
}

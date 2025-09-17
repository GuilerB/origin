#include <cmath>
#include <iostream>
#include <string>

void printHeap(int* arr, int size) {

    std::cout << "Исходный массив: ";
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            std::cout << " " << arr[i] << std::endl;
        }
        else {
            std::cout << " " << arr[i];
        }
    }

    std::cout << "Пирамида: ";
    std::cout << std::endl;
    int level = 0;
    for (int i = 0; i < size; i++) {

        int level = floor(log2(i + 1));

        if (i == 0) {
            std::cout << 0 << " root " << arr[i] << std::endl;
        }
        else if (i % 2 != 0) {
            int parIndex = (i - 1) / 2;
            std::cout << level << " left(" << arr[parIndex] << ") " << arr[i] << std::endl;
        }
        else if (i % 2 == 0) {
            int parIndex = (i - 1) / 2;
            std::cout << level << " right(" << arr[parIndex] << ") " << arr[i] << std::endl;
        }
    }
}

bool toLeftChild(int size, int& currIndex) {
    int childIndex = 2 * currIndex + 1;
    if (childIndex >= size) {
        std::cout << "Ошибка! Отсутствует левый потомок" << std::endl;
        return false;
    }
    currIndex = childIndex;
    return true;
}
 bool toRightChild(int size, int& currIndex) {
      int childIndex = 2 * currIndex + 2;
      if (childIndex >= size) {
          std::cout << "Ошибка! Отсутствует правый потомок" << std::endl;
          return false;
      }
      currIndex = childIndex;
      return true;
 }

 bool toParent(int& currIndex) {

    if (currIndex == 0) {
         std::cout << "Ошибка!Отсутствует родитель" << std::endl;
         return false;
    }
    if (currIndex % 2 != 0) {
        currIndex = (currIndex - 1) / 2;
    }
    else if (currIndex % 2 == 0) {
         currIndex = (currIndex - 2) / 2;
    }
    
    return true;
}

 void printOk() {
     std::cout << "Ok" << std::endl;
}

int main()
{

    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    std::string up = "up", left = "left", right = "right", exit = "exit";

    int arr1[] = { 1, 3, 6, 5, 9, 8 };
    int len1 = sizeof(arr1) / sizeof(arr1[0]);

    //int arr2[] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    //int len2 = sizeof(arr2) / sizeof(arr2[0]);

    //int arr3[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    //int len3 = sizeof(arr3) / sizeof(arr3[0]);

    printHeap(arr1, len1);
    std::cout << "\n";

    int i = 0;
    int level{0};

    do {
        level = floor(log2(i + 1));
        
        if (i == 0) {
            std::cout << "Вы находитесь здесь: " << level << " root " << arr1[i] << std::endl;
        }
        else if (i % 2 != 0) {
            int parIndex = (i - 1) / 2;
            std::cout << "Вы находитесь здесь: " << level << " left(" << arr1[parIndex] << ") " << arr1[i] << std::endl;
        }
        else if (i % 2 == 0) {
            int parIndex = (i - 2) / 2;
            std::cout << "Вы находитесь здесь: " << level << " right(" << arr1[parIndex] << ") " << arr1[i] << std::endl;
        }

        std::cout << "Введите команду: ";
        std::string comm{};
        std::cin >> comm;
        
        if (comm.compare(up) == 0 && toParent(i) == true) {
            printOk();
            continue;
        } 
        else if (comm.compare(left) == 0 && toLeftChild(len1, i) == true) {
            printOk();
            continue;
        }
        else if (comm.compare(right) == 0 && toRightChild(len1, i) == true) {
            printOk();
            continue;
        } 
        else if (comm.compare(exit) == 0) {
            return 0;
        }
        else if (comm.compare(up) != 0 && comm.compare(left) != 0 && comm.compare(right) != 0 && comm.compare(exit) != 0) {
            std::cout << "Некорректная команда, повторите ввод " << std::endl;
            continue;
        }      
    } while (true);

}
#include <cmath>
#include <iostream>

void printHeap(int *arr, int size) {
    
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
        } else if (i % 2 != 0) {
            int parIndex = (i - 1)/2;
            std::cout << level << " left(" << arr[parIndex] << ") " << arr[i] << std::endl;
        }
        else if (i % 2 == 0) {
            int parIndex = (i - 2) / 2;
            std::cout << level << " right(" << arr[parIndex] << ") " << arr[i] << std::endl;
        }
    }
}

int main()
{

    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    int arr1[] = { 1, 3, 6, 5, 9, 8 };
    int len1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    int len2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    int len3 = sizeof(arr3) / sizeof(arr3[0]);

    printHeap(arr1, len1);
    std::cout << "\n";
    printHeap(arr2, len2);
    std::cout << "\n";
    printHeap(arr3, len3);
}
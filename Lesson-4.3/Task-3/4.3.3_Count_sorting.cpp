#include <iostream>

void count_sort(int* arr, int size) {

    const int Nmax = 24;
    const int Nmin = 10;
    const int offset = Nmin;
    const int count_size = Nmax + 1 - offset;
    int c[count_size] = { 0 };

    for (int i = 0; i < size; i++) {
        c[arr[i] - offset]++;
    }

    int k = 0;
    for (int i = 0; i < count_size; i++) {
        while (c[i] != 0)
        {
            arr[k] = i + offset;
            k++;
            c[i]--;
        };
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    int arr1[] = { 19, 14, 22, 22, 17, 22, 13, 21, 20, 24, 18, 10, 17, 16, 17, 20, 22, 11, 20, 16, 14, 13, 10, 22, 18, 14, 16, 24, 19, 17 };
    int arr2[] = { 16, 17, 14, 20, 22, 20, 17, 22, 16, 19, 23, 24, 20, 22, 21, 18, 14, 16, 17, 21, 10, 11, 19, 23, 11, 11, 17, 17, 11, 21, 17, 11, 17, 16, 12, 11, 16, 22, 23, 16 };
    int arr3[] = { 21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17, 13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10 };

    int arr1_len = sizeof(arr1) / sizeof(arr1[0]);
    int arr2_len = sizeof(arr2) / sizeof(arr2[0]);
    int arr3_len = sizeof(arr3) / sizeof(arr3[0]);

    std::cout << "Исходный массив: ";
    printArray(arr1, arr1_len);
    count_sort(arr1, arr1_len);
    std::cout << "Отсортированный массив: ";
    printArray(arr1, arr1_len);

    std::cout << std::endl;
    std::cout << "Исходный массив: ";
    printArray(arr2, arr2_len);
    count_sort(arr2, arr2_len);
    std::cout << "Отсортированный массив: ";
    printArray(arr2, arr2_len);

    std::cout << std::endl;
    std::cout << "Исходный массив: ";
    printArray(arr3, arr3_len);
    count_sort(arr3, arr3_len);
    std::cout << "Отсортированный массив: ";
    printArray(arr3, arr3_len);

}

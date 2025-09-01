#include <iostream>

int numLargerElements(const int arr[], int size, int number) {
    int low = 0;
    int high = size;

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > number) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }
    return size - low;
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";
    while (true) {
        int array[] = { 14, 16, 19, 32, 32, 32, 56, 69, 72 };
        int size = sizeof(array) / sizeof(array[0]);
        int num{ 0 };

        std::cout << "Введите точку отсчёта: ";
        std::cin >> num;

        int count = numLargerElements(array, size, num);
        std::cout << "Количество элементов в массиве больших, чем " << num << ": " << count << std::endl;

    }
}
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
void sort_vector(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end(), std::less<T>());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
}
template <typename T>
void print_vector(std::vector<T>& vec) {
    for (int element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    std::vector<int> vector{ 1, 1, 2, 5, 6, 1, 2, 4 };

    std::cout << "[IN]" << ": ";
    print_vector(vector);
    sort_vector(vector);
    std::cout << "[OUT]" << ": ";
    print_vector(vector);

    return 0;
}
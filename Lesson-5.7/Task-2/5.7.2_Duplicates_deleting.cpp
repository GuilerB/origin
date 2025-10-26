#include <iostream>
#include <algorithm>
#include <vector>


template <typename T>
void fill_vector(std::vector<T>& vec, int size) {
    int counter{ 0 };
    T number;
    while (counter < size)
    {
        std::cin >> number; 
        vec.push_back(number);  
        counter++;
    }
}
template <typename T>
void sort_vector(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end(), std::greater<T>());
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

    int vector_size{ 0 };
    
    std::vector<int> vector;

    std::cout << "IN" << ": " << std::endl;
    std::cin >> vector_size;
    fill_vector(vector, vector_size);
    sort_vector(vector);
    std::cout << "OUT" << ": " << std::endl;
    print_vector(vector);

    return 0;
}
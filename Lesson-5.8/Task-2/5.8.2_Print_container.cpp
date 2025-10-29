#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>

template <typename T>
void print_container(T& cont) {
    for (std::string element : cont) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    std::vector<std::string> test_vector{ "one", "two", "three", "four" };
    std::set<std::string> test_set{ "one", "two", "three", "four" };
    std::list<std::string> test_list{ "one", "two", "three", "four" };

    std::cout << "test_set" << ": ";
    print_container(test_set);

    std::cout << "test_list" << ": ";
    print_container(test_list);

    std::cout << "test_vector" << ": ";
    print_container(test_vector);

    return 0;
}
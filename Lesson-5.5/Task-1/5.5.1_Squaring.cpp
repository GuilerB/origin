#include <iostream>
#include <vector>

template<typename T>
T square(T a) { return a * a; }

template<typename T>
void square(std::vector<T>& vector) {
    for (auto& elem : vector) {
        elem = elem * elem;
    }
}

template<typename T>
void printVector(std::vector<T>& vector) {
    for (auto elem_id = vector.begin(); elem_id != vector.end() - 1; ++elem_id) {
        std::cout << *elem_id << ", ";
    }
    std::cout << vector.back();
}

int main()
{
    int val{ 4 };
    std::vector<int> vec{ -1, 4, 8 };
    
    std::cout << "[IN]: " << val << std:: endl;
    std::cout << "[OUT]: " << square(val);
    std::cout << std::endl;

    std::cout << "[IN]: ";
    printVector(vec);
    std::cout << std::endl;
    
    std::cout << "[OUT]: ";
    square(vec);
    printVector(vec);
    std::cout << std::endl;
}

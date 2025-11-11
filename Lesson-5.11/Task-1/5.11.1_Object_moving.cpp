#include <iostream>
#include <vector>

template <typename T>
void move_vectors(std::vector<T>& lhs, std::vector<T>& rhs)
{   
    rhs = std::move(lhs);
}

template <typename T>
void print_vector(std::vector<T>& vector)
{
    for (const T& s : vector) {
        std::cout << s << std::endl;
    }
}

int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    
    std::cout << "one before moving: " << std::endl;
    print_vector(one);

    std::cout << std::endl;
    std::cout << "two before moving: " << std::endl;
    print_vector(two);

    std::cout << std::endl;

    move_vectors(one, two);

    std::cout << "one after moving: " << std::endl;
    print_vector(one);

    std::cout << std::endl;
    std::cout << "two after moving: " << std::endl;
    print_vector(two);

}
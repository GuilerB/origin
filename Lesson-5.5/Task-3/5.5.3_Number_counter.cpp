#include <iostream>
#include <algorithm>
#include <vector>

class functor {
private:
    int count;
    int sum;
public:
    functor() : count(0), sum(0) {}

    void operator()(std::vector<int>& vec) {
        for (int num : vec) {
            if (num % 3 == 0) {
                sum += num;
                count++;
            }
        }
    }
    int get_sum() { return sum; }
    int get_count() { return count; }
};

template<typename T>
void printVector(std::vector<T>& vector) {
    for (auto elem_id = vector.begin(); elem_id != vector.end() - 1; ++elem_id) {
        std::cout << *elem_id << ", ";
    }
    std::cout << vector.back();
}

int main()
{
    std::vector<int> vec = { 4, 1, 3, 6, 25, 54 };
    
    functor sum_n_count;
    sum_n_count(vec);
    
    std::cout << "[IN]: "; printVector(vec); std::cout << std::endl;
    std::cout << "[OUT]: " << "get_sum() = " << sum_n_count.get_sum(); std::cout << std::endl;
    std::cout << "[OUT]: " << "get_count() = " << sum_n_count.get_count(); std::cout << std::endl;

}

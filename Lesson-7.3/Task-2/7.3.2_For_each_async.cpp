#include <execution>
#include <functional>
#include <iterator>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <iostream>

template<typename Iterator, typename Func>
void for_each_parallel(Iterator first, Iterator last, Func& func, size_t min_chunk_size = 10) {
    auto distance = std::distance(first, last);
    if (distance <= static_cast<long long>(min_chunk_size)) {
        // ordinary func if size less or equal
        std::for_each(first, last, func);
    }
    else {
        auto mid = first;
        std::advance(mid, distance / 2);

        // Recursive 1st half in a separate task
        auto res = std::async(std::launch::async, [&] {
            for_each_parallel(first, mid, func, min_chunk_size);
            });

        // 2nd half in the current thread
        for_each_parallel(mid, last, func, min_chunk_size);

        res.wait();
    }
}

int main() {
    std::vector<int> data(30, 3);
    
    for (int x : data) { std::cout << x << "  "; }
    std::cout << std::endl;

    auto func = [](int& x) { x *= 5; };

    for_each_parallel(data.begin(), data.end(), func);

    for (int x : data) { std::cout << x << " "; }
    std::cout << std::endl;

    return 0;
}
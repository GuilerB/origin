#include <iostream>
#include <vector>
#include <thread>
#include <future>


// simple func to search for min and set a promise value
void find_min_set_promise(const std::vector<int>& arr, size_t start, std::promise<size_t> prom) {
    size_t min_idx = start;
    for (size_t i = start + 1; i < arr.size(); ++i) {
        if (arr[i] < arr[min_idx]) {
            min_idx = i;
        }
    }
    prom.set_value(min_idx);
}

// Asyncronous wrapper-function
std::future<size_t> find_min_async(const std::vector<int>& arr, size_t start) {
    std::promise<size_t> prom;
    auto fut = prom.get_future();

    std::thread thr(find_min_set_promise, std::cref(arr), start, std::move(prom));
    thr.detach(); 

    return fut;
}

// swap function using other functions
void selection_sort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        auto fut = find_min_async(arr, i);
        size_t min_idx = fut.get();

        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }
}

int main() {
    std::vector<int> data = { 63, 17, 12, 10, 11, -100, 4, 0, 17 };

    selection_sort(data);

    for (int x : data) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
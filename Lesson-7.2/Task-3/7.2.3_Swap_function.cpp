#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
    int value = 0;
    mutable std::mutex mtx;

    Data(int v = 0) : value(v) {}
};

void swap_with_lock(Data& a, Data& b) {
    std::lock(a.mtx, b.mtx);
    std::lock_guard<std::mutex> lock_a(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(b.mtx, std::adopt_lock);

    using std::swap;
    swap(a.value, b.value);
}

void swap_with_scoped_lock(Data& a, Data& b) {
    std::scoped_lock lock(a.mtx, b.mtx);
    using std::swap;
    swap(a.value, b.value);
}

void swap_with_unique_lock(Data& a, Data& b) {
    std::unique_lock<std::mutex> lock_a(a.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(b.mtx, std::defer_lock);
    std::lock(lock_a, lock_b);

    using std::swap;
    swap(a.value, b.value);
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // fixing console coding index
    std::cout << "\n\n\n";

    Data d1(10);
    Data d2(50);

    std::cout << "Исходные значения: d1=" << d1.value << ", d2=" << d2.value << std::endl; std::cout << "\n";

    swap_with_lock(d1, d2);
    std::cout << "После lock: d1=" << d1.value << ", d2=" << d2.value << std::endl; std::cout << "\n";

    swap_with_scoped_lock(d1, d2);
    std::cout << "После scoped_lock: d1=" << d1.value << ", d2=" << d2.value << std::endl; std::cout << "\n";

    swap_with_unique_lock(d1, d2);
    std::cout << "После unique_lock: d1=" << d1.value << ", d2=" << d2.value << std::endl;

    return 0;
}
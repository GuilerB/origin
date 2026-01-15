#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// Client function with memory_order_seq_cst
void customerThread_seq_cst(std::atomic<int>& count, const int max) {
    bool running = true;
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int current = count.load(std::memory_order_seq_cst);
        if (current < max) {
            if (count.compare_exchange_weak(current, current + 1, std::memory_order_seq_cst)) {
                std::cout << "Новый клиент. Всего: " << count.load(std::memory_order_seq_cst) << std::endl;
            }
        }
        else {
            running = false;
        }
    }
}

// Operationist function with memory_order_seq_cst
void operationistThread_seq_cst(std::atomic<int>& count) {
    bool running = true;
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        int current = count.load(std::memory_order_seq_cst);
        if (current > 0) {
            if (count.compare_exchange_weak(current, current - 1, std::memory_order_seq_cst)) {
                std::cout << "Клиент обслужен. Осталось: " << count.load(std::memory_order_seq_cst) << std::endl;
            }
        }
        else {
            running = false;
        }
    }
}

// Client function with memory_order_relaxed
void customerThread_seq_rlxd(std::atomic<int>& count, const int max) {
    bool running = true;
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int current = count.load(std::memory_order_relaxed);
        if (current < max) {
            if (count.compare_exchange_weak(current, current + 1, std::memory_order_relaxed)) {
                std::cout << "Новый клиент. Всего: " << count.load(std::memory_order_relaxed) << std::endl;
            }
        }
        else {
            running = false;
        }
    }
}

// Operationist function with memory_order_relaxed
void operationistThread_seq_rlxd(std::atomic<int>& count) {
    bool running = true;
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        int current = count.load(std::memory_order_relaxed);
        if (current > 0) {
            if (count.compare_exchange_weak(current, current - 1, std::memory_order_relaxed)) {
                std::cout << "Клиент обслужен. Осталось: " << count.load(std::memory_order_relaxed) << std::endl;
            }
        }
        else {
            running = false;
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::cout << "\n\n";

    std::atomic<int> customer_count_seq_cst{ 0 };
    std::atomic<int> customer_count_seq_rlxd{ 0 };

    const int MAX_CUSTOMERS = 10;

    std::cout << "= Атомарно через memory_order_seq_cst = " << std::endl;

    std::thread customer_seq_cst(customerThread_seq_cst, std::ref(customer_count_seq_cst), MAX_CUSTOMERS);
    std::thread operationist_seq_cst(operationistThread_seq_cst, std::ref(customer_count_seq_cst));

    customer_seq_cst.join();
    operationist_seq_cst.join();
    
    std::cout << "\n";

    std::cout << "= Атомарно через memory_order_release = " << std::endl;

    std::thread customer_seq_rlxd(customerThread_seq_rlxd, std::ref(customer_count_seq_rlxd), MAX_CUSTOMERS);
    std::thread operationist_seq_rlxd(operationistThread_seq_rlxd, std::ref(customer_count_seq_rlxd));

    customer_seq_rlxd.join();
    operationist_seq_rlxd.join();
    
    return 0;
}
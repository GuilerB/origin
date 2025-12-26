#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Client function
void customerThread(std::mutex& mtx, int& count, const int max, bool& running_cust) {
    while (running_cust) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        mtx.lock();
        if (count < max) {
            count++;
            std::cout << "Новый клиент. Всего: " << count << std::endl;
        }
        else if (count == max) { running_cust = false; }       // stop adding clients after max        
        
        mtx.unlock();
    }
}

// Operationist function
void operationistThread(std::mutex& mtx, int& count, bool& running_op) {
    while (running_op) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        mtx.lock();
        if (count > 0) {
            count--;
            std::cout << "Клиент обслужен. Осталось: " << count << std::endl;
        }
        else if (count == 0) { running_op = false; }          // work till the latest client is operated
        
        mtx.unlock();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // fixing console coding index
    std::cout << "\n\n\n";

    std::mutex mtx;
    int customer_count = 0;
    const int MAX_CUSTOMERS = 10;
    bool running_customer = true;
    bool running_operationist = true;

    std::cout << "= начало =" << std::endl;

    std::thread customer(customerThread, std::ref(mtx), std::ref(customer_count), MAX_CUSTOMERS, std::ref(running_customer));

    std::thread operationist(operationistThread, std::ref(mtx), std::ref(customer_count), std::ref(running_operationist));

    if (customer.joinable() && operationist.joinable()) {
        customer.join();
        operationist.join();
    }
   
    return 0;
}
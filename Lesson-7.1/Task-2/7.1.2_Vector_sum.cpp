#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <cmath>

void add_vectors_part(std::vector<double>& a, std::vector<double>& b,
    std::vector<double>& result, int start, int end) {
    for (int i = start; i < end; ++i) {
        result[i] = a[i] + b[i];
    }
}

double measure_time(int num_threads, int size) {
    std::vector<double> a(size);
    std::vector<double> b(size);
    std::vector<double> result(size);

    for (int i = 0; i < size; ++i) {
        a[i] = i * 1.5;
        b[i] = i * 0.1;
    }

    int block_size = size / num_threads;

    std::vector<std::thread> threads;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        int start = i * block_size;
        int end = (i == num_threads - 1) ? size : (i + 1) * block_size;

        threads.emplace_back(add_vectors_part, std::ref(a), std::ref(b),
            std::ref(result), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end_time - start_time;

    return duration.count();
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // fixing console coding index
    std::cout << "\n\n\n";


    int cores = std::thread::hardware_concurrency();
    std::cout << "Доступно аппаратных ядер: " << cores << std::endl;
    std::cout << "==============================================" << std::endl;

    std::vector<int> sizes = { 1000, 10000, 100000, 1000000 };

    std::vector<int> thread_counts = { 1, 2, 4, 8, 16 };

    std::vector<std::vector<double>> results(
        thread_counts.size(),
        std::vector<double>(sizes.size(), 0.0)
    );

    for (size_t i = 0; i < thread_counts.size(); ++i) {
        for (size_t j = 0; j < sizes.size(); ++j) {
            results[i][j] = measure_time(thread_counts[i], sizes[j]);
        }
    }

    std::cout << "\nВремя выполнения (мс):\n";
    std::cout << std::string(100, '-') << std::endl;
    std::cout << std::string(23, ' ');
    
    for (int size : sizes) {
        std::cout << size << std::string(9, ' ');
    }

    std::cout << std::endl;
    std::cout << std::string(100, '-') << std::endl;

    for (size_t i = 0; i < thread_counts.size(); ++i) {
        std::cout << std::setw(10) << thread_counts[i] << "  |";
        for (size_t j = 0; j < sizes.size(); ++j) {
            std::cout << std::setw(14) << std::fixed
                << std::setprecision(4) << results[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;

struct ThreadData {
    int progress = 0;
    bool finished = false;
    long long time_ms = 0;
    std::thread::id id;
};

void worker(int thread_num, int length, std::vector<ThreadData>& data) {
    data[thread_num].id = std::this_thread::get_id();
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i <= length; ++i) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            data[thread_num].progress = i;
            if (i == length) {
                auto end = std::chrono::high_resolution_clock::now();
                data[thread_num].time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                data[thread_num].finished = true;
            }

            // Очистка консоли (переводы строк)
            for (size_t clear = 0; clear < data.size() + 3; ++clear) {
                std::cout << "\033[1A\033[2K";  
            }

            std::cout << "No\tID\t\tProgress\tTime\n";
            for (size_t t = 0; t < data.size(); ++t) {
                std::cout << (t + 1) << "\t" << data[t].id << "\t["
                    << std::string(data[t].progress, '*')
                    << std::string(length - data[t].progress, ' ') << "]";
                if (data[t].finished) {
                    std::cout << "\t" << data[t].time_ms << "ms";
                }
                std::cout << "\n";
            }
        }
        if (i < length) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
}

int main() {
    int num_threads = 5;
    int calc_length = 15;

    std::vector<ThreadData> data(num_threads);
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i, calc_length, std::ref(data));
    }

    for (auto& t : threads) t.join();

    return 0;
}
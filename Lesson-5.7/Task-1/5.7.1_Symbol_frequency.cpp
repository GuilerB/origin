#include <iostream>
#include <algorithm>

#include <unordered_map>
#include <vector>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";   

    std::string text = "Я вас категорически приветствую! - Всем привет!";

    std::unordered_map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }

    std::vector<std::pair<char, int>> sorted_frequency(frequency.begin(), frequency.end());

    std::sort(sorted_frequency.begin(), sorted_frequency.end(),
        [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
            return a.second > b.second;
        });

    std::cout << "'" << "IN" << ": " << text << std::endl;
    std::cout << "'" << "OUT" << ": " << std::endl;

    for (const auto& pair : sorted_frequency) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
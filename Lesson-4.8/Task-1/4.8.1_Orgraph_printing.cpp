#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 


int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }
    int N{ 0 };

    file >> N;

    int rows = N; int cols = N;
    std::string line;
    std::string first_line;

    std::getline(file, first_line);

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols]();
    }

    std::cout << "Текстовый вид орграфа: ";
    std::cout << std::endl;

    int row = 0;
    while (std::getline(file, line)) {

        std::istringstream iss(line);
        int value;
        int col = 0;
        
        int sum{ 0 };
        std::cout << row + 1 << ": ";
        while (iss >> value && col < cols) {
            matrix[row][col] = value;
            if (matrix[row][col] == 1) {
                std::cout << col+1 << " ";
                sum = sum + 1;
            }            
            col++;
        }
        if (sum == 0) { std::cout << "нет"; }

        std::cout << std::endl;
        row++;
    }

    file.close();


    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
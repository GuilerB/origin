#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

void dfs(int** graph, bool* visited, int curr, int size, int* stack,int &stackIndex) {
   
    for (int i = 0; i < size; i++) {
        if (graph[curr][i] == 1 && !visited[i]) {
            dfs(graph, visited, i, size, stack, stackIndex);
        }
    }
    visited[curr] = true;

    stack[stackIndex] = curr;
    stackIndex++;
}

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

    int** matrix = new int* [rows];

    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[N];
        for (int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }

    file.close();

    bool* visited = new bool[N];

    for (int i = 0; i < N; i++) {
        visited[i] = false;
    }

    int* stack = new int[N];
    int stackIndex = 0;
    for (int i = 0; i < N; i++) {
        if (visited[i] == false) {
            dfs(matrix, visited, i, N, stack, stackIndex);
        }
    }

    std::cout << "Топологический порядок: ";
    for (int i = stackIndex - 1; i >= 0; i--) {
        std::cout << stack[i] + 1 << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] visited;
    delete[] stack;

    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

    void dfs(int** graph, bool* visited, int curr, int size) {
        visited[curr] = true;
        std::cout << curr + 1 << " ";

        for (int i = 0; i < size; i++) {
            if (graph[curr][i] == 1 && !visited[i]) {
                dfs(graph, visited, i, size);
            }
        }
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
            
        std::getline(file, first_line);        
            
        int** matrix = new int* [rows];            
        for (int i = 0; i < rows; i++) { 
            matrix[i] = new int[cols](); 
        }       
            
        int row = 0;            
        while (std::getline(file, line)) {       
                
            std::istringstream iss(line);                
            int value;                
            int col = 0;        
                
            while (iss >> value && col < cols) {                    
                matrix[row][col] = value;                    
                col++;                
            }                
            row++;            
        }
            
        file.close();

        bool* visited = new bool[N] {false};

        std::cout << "Порядок обхода вершин: ";
        dfs(matrix, visited, 0, N);
        std::cout << std::endl;

        for (int i = 0; i < N; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] visited;

        return 0;
    }
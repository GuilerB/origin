#include <iostream>
#include <vector>

template<typename T>
class table {

public:
    table(size_t numRows, size_t numCols) : rows(numRows), cols(numCols) {
        if (rows == 0 || cols == 0) {
            throw std::invalid_argument("Размеры должны быть > 0!!!");
        }
        data.resize(rows, std::vector<T>(cols));
    }

    std::vector<T>& operator[](size_t row) {
        if (row >= rows) {
            throw std::out_of_range("Индекс за границами таблицы");
        }
        return data[row];
    }

    const std::vector<T>& operator[](size_t row) const {
        if (row >= rows) {
            throw std::out_of_range("Индекс за границами таблицы");
        }
        return data[row];
    }

    size_t Size() const { return rows * cols; }

    void fill_def_val(const T& value) {
        for (auto& row : data) {
            for (auto& elem : row) {
                elem = value;
            }
        }
    }
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n";

    try {
        auto test = table<int>(2, 3);
        test.fill_def_val(2);
        test[0][0] = 4;
        std::cout << test[0][0] << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

}

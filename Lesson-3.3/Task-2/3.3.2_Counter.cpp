#include <iostream>

class Counter {
private:
    long count;

public:
    Counter() {
        count = 1;
    }
    Counter(long& value) {
        count = value;
    }

    void add() {
        count = count + 1;
    }
    void subtract() {
        count = count - 1;
    }
    void print_val() {
        std::cout << this->count << std::endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n";

    char oper{ '0' };
    std::string check_init{ "0" };

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    while (true){
        std::cin >> check_init;
        if (check_init == "да") {
            std::cout << "введите начальное значение счётчика: ";
            long init_value;
            std::cin >> init_value;
            Counter counter(init_value);
            while (true) {
                std::cout << "Введите команду ('+', '-', '=' или '*'): ";
                std::cin >> oper;
                switch (oper) {
                case ('+'): counter.add(); break;
                case ('-'):  counter.subtract(); break;
                case ('=') : counter.print_val(); break;
                case ('*'):
                    std::cout << "До свидания!";
                    return 0;
                }
            }
        }
        else if (check_init == "нет") {
            Counter counter;
            while (true) {    
                std::cout << "Введите команду ('+', '-', '=' или '*'): ";
                std::cin >> oper;
                switch (oper) {
                case ('+'): counter.add(); break;
                case ('-'):  counter.subtract(); break;
                case ('='): counter.print_val(); break;
                case ('*'):
                    std::cout << "До свидания!";
                    return 0;
                }
            }
        }
        else {
            std::cout << "Введите да или нет: ";
        }
    }
}


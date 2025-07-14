#include <iostream>

class Calculator {
public:
    double num1{ 0 }, num2{ 0 };

    double add() {
        return num1 + num2;
    };
    double multiply() {
        return num1 * num2;
    };
    double subtract_1_2() {
        return num1 - num2;
    };
    double subtract_2_1() {
        return num2 - num1;
    };
    double divide_1_2() {
        return num1 / num2;
    };
    double divide_2_1() {
        return num2 / num1;
    };
    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        }
        else {
            return false;
        }
    }
    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        }
        else {
            return false;
        }
    };

};

int main()
{
    Calculator calculator;
    while (true) {
        std::cout << "Input num1: ";
        std::cin >> calculator.num1;
        while (calculator.set_num1(calculator.num1) == false) {
            std::cout << "Invalid input! num1 equal to 0" << std::endl;
            std::cout << "Input num1: ";
            std::cin >> calculator.num1;
        }
        
        std::cout << "Input num2: ";
        std::cin >> calculator.num2;       

        while (calculator.set_num2(calculator.num2) == false) {
            std::cout << "Invalid input! num2 equal to 0" << std::endl;
            std::cout << "Input num2: ";
            std::cin >> calculator.num2;
        }

        std::cout << "num1 + num2 = " << calculator.add() << std::endl;
        std::cout << "num1 - num2 = " << calculator.subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << calculator.subtract_2_1() << std::endl;
        std::cout << "num1 * num2 = " << calculator.multiply() << std::endl;
        std::cout << "num1 / num2 = " << calculator.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << calculator.divide_2_1() << std::endl;
    }

}


#include <iostream>

enum class months
{
    Январь = 1,
    Февраль,
    Март,
    Апрель,
    Май,
    Июнь,
    Июль,
    Август,
    Сентябрь,
    Октябрь,
    Ноябрь,
    Декабрь
};

int main()
{
    setlocale(LC_ALL, "Russian");

    while (true) {
        int month_num{};

        std::cout << "Введите номер месяца: ";
        std::cin >> month_num;

        if (month_num > 12 || month_num < 0) {
            std::cout << "Неправильный номер!" << std::endl;
            //break;
        }
        else if (month_num == 0) {
            std::cout << "До свидания" << std::endl;
            break;
        }

        months month = static_cast<months>(month_num);

        switch (month) {
        case months::Январь:
            std::cout << "Январь" << std::endl; break;
        case months::Февраль:
            std::cout << "Февраль" << std::endl; break;
        case months::Март:
            std::cout << "Март" << std::endl; break;
        case months::Апрель:
            std::cout << "Апрель" << std::endl; break;
        case months::Май:
            std::cout << "Май" << std::endl; break;
        case months::Июнь:
            std::cout << "Июнь" << std::endl; break;
        case months::Июль:
            std::cout << "Июль" << std::endl; break;
        case months::Август:
            std::cout << "Август" << std::endl; break;
        case months::Сентябрь:
            std::cout << "Сентябрь" << std::endl; break;
        case months::Октябрь:
            std::cout << "Октябрь" << std::endl; break;
        case months::Ноябрь:
            std::cout << "Ноябрь" << std::endl; break;
        case months::Декабрь:
            std::cout << "Декабрь" << std::endl; break;
        }
    }
}
#include <iostream>

class bad_length : public std::exception
{
public:
    const char* what() const override { return "Вы ввели слово запретной длины! До свидания"; }
};

int function(std::string str, int forbidden_length) {

    if (str.length() == forbidden_length) 
        throw bad_length();
    return str.length();      
}
int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    std::string inText;
    int inForbiddenLen{ 0 }, textLen{ 0 };

    std::cout << "Введите запретную длину: ";
    std::cin >> inForbiddenLen;

    while (true) {
        try
        {
            std::cout << "Введите слово: ";
            std::cin >> inText;
            textLen = function(inText, inForbiddenLen);
            std::cout << "Длина слова \"" << inText << "\" равна " << textLen << std::endl;
        }
        catch (const bad_length& e) { std::cout << e.what() << std::endl; break; }
        catch (...) { std::cout << "Неизвестная ошибка" << std::endl; break; }
    }

}


#include <iostream>
#include <string>

int main() {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251"); // настраиваем кодировку консоли
	std::cout << "\n\n\n"; 
	
	std::string name{};

	std::cout << "Введите  имя: ";
	std::cin >> name;

	std::cout << "Здравствуйте, " << name << "!" << std::endl;

	return 0;
}

#include <iostream>

class Figure
{

public:
    int get_sides_count() { return sides_count; };
    std::string get_name() { return name; };

    Figure() { sides_count = 0; name = "Фигура"; }

protected:
    int sides_count;
    std::string name;
};

class Triangle : public Figure
{
public:
    Triangle() { sides_count = 3; name = "Треугольник"; }
};

class Quadrangle : public Figure
{
public:
    Quadrangle() { sides_count = 4; name = "Четырехугольник"; }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "Количество сторон: \n";

    Figure figure;
    Triangle triangle;
    Quadrangle quadrangle;

    std::cout << figure.get_name() << ": " << figure.get_sides_count() << std::endl;
    std::cout << triangle.get_name() << ": " << triangle.get_sides_count() << std::endl;
    std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count() << std::endl;
}


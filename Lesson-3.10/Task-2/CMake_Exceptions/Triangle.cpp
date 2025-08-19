#include <iostream>
#include "Triangle.h"
#include "FigureCreationExc.h"

    double Triangle::get_side_a() { return a; };
    double Triangle::get_side_b() { return b; };
    double Triangle::get_side_c() { return c; };
    double Triangle::get_angle_A() { return A; };
    double Triangle::get_angle_B() { return B; };
    double Triangle::get_angle_C() { return C; };

    void Triangle::print_info() {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Triangle::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C;
        if (num_sides == 3 && sumAngles == 180.) { return true; }
        else { return false; }
    }

    Triangle::Triangle() :Triangle(a, b, c, A, B, C) {
        double sum = A + B + C;
        if (sum != 180) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: сумма углов не равна 180");
        }
        if (sides_count != 3) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: Количество сторон не равно 3");
        }
    }

    Triangle::Triangle::Triangle(double a, double b, double c, double A, double B, double C)
    {
        sides_count = 3; name = "Треугольник";
    }

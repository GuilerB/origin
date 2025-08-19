#include <iostream>
#include "Quadrangle.h"
#include "FigureCreationExc.h"

    double Quadrangle::get_side_a()  { return a; };
    double Quadrangle::get_side_b()  { return b; };
    double Quadrangle::get_side_c()  { return c; };
    double Quadrangle::get_side_d()  { return d; };
    double Quadrangle::get_angle_A()  { return A; };
    double Quadrangle::get_angle_B()  { return B; };
    double Quadrangle::get_angle_C()  { return C; };
    double Quadrangle::get_angle_D()  { return D; };

    void Quadrangle::print_info() {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Quadrangle::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C + D;
        if (num_sides == 4 && sumAngles == 360.) { return true; }
        else { return false; }
    }

    Quadrangle::Quadrangle() : Quadrangle(a, b, c, d, A, B, C, D) {
        double sum = A + B + C + D;
        if (sum != 360) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: сумма углов не равна 360");
        }
        if (sides_count != 4) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: Количество сторон не равно 4");
        }
    }

    Quadrangle::Quadrangle(double a, double b, double c, double d, double A, double B, double C, double D)
    {
        sides_count = 4; name = "Четырехугольник";
    }



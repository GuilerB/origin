#include "Triangle_equalAllSides.h"
#include "FigureCreationExc.h"

    Triangle_equalAllSides::Triangle_equalAllSides() :Triangle_equalAllSides(a) {
        double sum = A + B + C;
        if (a != b || c != a || c != b) { throw FigureCreationError("Ошибка создания фигуры. Причина: стороны не равны"); }
        if (A != B || C != A || C != B) { throw FigureCreationError("Ошибка создания фигуры. Причина: углы не равны"); }
        if (A != 60 || B != 60 || C != 60) { throw FigureCreationError("Ошибка создания фигуры. Причина: один из углов не равен 60"); }
        if (sum != 180) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: сумма углов не равна 180");
        }
        if (sides_count != 3) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: Количество сторон не равно 3");
        }
    }

    void Triangle_equalAllSides::print_info() {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Triangle_equalAllSides::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C;
        if (num_sides == 3 && sumAngles == 180. && c == a && c == b && A == C && C == B) { return true; }
        else { return false; }
    }

    Triangle_equalAllSides::Triangle_equalAllSides(double a) : Triangle(a, b, c, A, B, C)
    {
        sides_count = 3; name = "Равносторонний треугольник";
        A = 60.0;
        c = Triangle::a; b = Triangle::a;
        C = A; B = A;
    }


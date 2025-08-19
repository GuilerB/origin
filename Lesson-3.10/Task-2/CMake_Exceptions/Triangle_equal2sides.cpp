#include "Triangle_equal2sides.h"
#include "FigureCreationExc.h"

    Triangle_equal2sides::Triangle_equal2sides() : Triangle_equal2sides(a, b, A, B) {
        double sum = A + B + C;
        if (a != c) { throw FigureCreationError("Ошибка создания фигуры. Причина: стороны 'a' и 'c' не равны"); }
        if (A != C) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: углы 'A' и 'C' не равны");
        }
        if (sum != 180) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: сумма углов не равна 180");
        }
        if (sides_count != 3) {
            throw FigureCreationError("Ошибка создания фигуры. Причина: Количество сторон не равно 3");
        }
    }

    void Triangle_equal2sides::print_info()  {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Triangle_equal2sides::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C;
        if (num_sides == 3 && sumAngles == 180. && c == a && A == C) { return true; }
        else { return false; }
    }

    Triangle_equal2sides::Triangle_equal2sides(double a, double b, double A, double B) : Triangle(a, b, c, A, B, C)
    {
        sides_count = 3; name = "Равнобедренный треугольник";
        c = Triangle::a; C = Triangle::A;
    }



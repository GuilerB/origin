#include "Quadrangle_PrUg.h"
#include "FigureCreationExc.h"

    Quadrangle_PrUg::Quadrangle_PrUg() : Quadrangle_PrUg(a, b) {
        if (a != c || b != d) { throw FigureCreationError("Ошибка создания фигуры. Стороны 'a' и 'c' или 'b' и 'd' не равны"); }
        if (A != 90 || B != 90 || C != 90 || D != 90) { throw FigureCreationError("Ошибка создания фигуры. Причина: некоторые из углов не равны 90"); }
    }
    void Quadrangle_PrUg::print_info()  {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << ", " << get_side_d() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ", " << get_angle_D() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Quadrangle_PrUg::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C + D;
        if (num_sides == 4 && sumAngles == 360. && a == c && b == d && A == C && A == B && B == D && D == 90.) {
            return true;
        }
        else { return false; }
    }

    Quadrangle_PrUg::Quadrangle_PrUg(double a, double b) : Quadrangle_PrllGrmm(a, b, A, B)
    {
        sides_count = 4; name = "Прямоугольник";
        A = 90.0;
        c = Quadrangle_PrllGrmm::a; d = Quadrangle_PrllGrmm::b;
        C = A; B = A; D = A;
    }


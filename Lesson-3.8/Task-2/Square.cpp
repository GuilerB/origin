#include "Square.h"
#include "FigureCreationExc.h"

    Square::Square() :Square(a) {
        if (a != c || b != d || a != d || a != b || b != c || c != d) { throw FigureCreationError("Ошибка создания фигуры. Причина: некоторые стороны не равны"); }
        if (A != 90 || B != 90 || C != 90 || D != 90) { throw FigureCreationError("Ошибка создания фигуры. Причина: некоторые углы не равны 90"); }
    }

    void Square::print_info() {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << ", " << get_side_d() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ", " << get_angle_D() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Square::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C + D;
        if (num_sides == 4 && sumAngles == 360. && a == c && a == b && a == d && A == C && A == B && B == D && D == 90.) {
            return true;
        }
        else { return false; }
    }

    Square::Square(double a) : Quadrangle_PrUg(a, b)
    {
        sides_count = 4; name = "Квадрат";
        c = Quadrangle_PrUg::a; d = Quadrangle_PrUg::a; b = Quadrangle_PrUg::a;
        C = Quadrangle_PrUg::A; B = Quadrangle_PrUg::A; D = Quadrangle_PrUg::A;
    }

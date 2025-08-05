#include "Romb.h"
//#include "FigureCreationExc.h"

    Romb::Romb() : Romb(a, A, B) {
        if (a != c || b != d || a != d || a != b || b != c || c != d) { throw FigureCreationError("Ошибка создания фигуры. Причина: некоторые стороны не равны"); }
        if (A != C || B != D) { throw FigureCreationError("Ошибка создания фигуры. Причина: Углы 'A' и 'C' или 'B' и 'D' не равны"); }

    }

    void Romb::print_info()  {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << ", " << get_side_d() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ", " << get_angle_D() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Romb::check()  {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C + D;
        if (num_sides == 4 && sumAngles == 360. && a == b && a == c && b == d &&
            A == C && B == D) {
            return true;
        }
        else { return false; }
    }

    Romb::Romb(double a, double A, double B) : Quadrangle_PrllGrmm(a, b, A, B)
    {
        sides_count = 4; name = "Ромб";
        c = Quadrangle_PrllGrmm::a; d = Quadrangle_PrllGrmm::a; b = Quadrangle_PrllGrmm::a;
        C = Quadrangle_PrllGrmm::A; D = Quadrangle_PrllGrmm::B;
    }


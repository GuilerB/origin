#include "Quadrangle_PrllGrmm.h"
#include "FigureCreationExc.h"

    Quadrangle_PrllGrmm::Quadrangle_PrllGrmm() :Quadrangle_PrllGrmm(a, b, A, B) {
        if (a != c || b != d) { throw FigureCreationError("Ошибка создания фигуры. Причина: стороны 'a' и 'c' или 'd' и 'b' не равны"); }
        if (A != C || B != D) { throw FigureCreationError("Ошибка создания фигуры. Причина: углы 'A' и 'C' или 'B' и 'D' не равны"); }
    }

    void Quadrangle_PrllGrmm::print_info()  {
        Figure::print_info();
        std::cout << "(cтороны " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << ", " << get_side_d() << "; ";
        std::cout << "углы " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ", " << get_angle_D() << ") ";
        std::cout << "создан" << std::endl;
    }
    bool Quadrangle_PrllGrmm::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C + D;
        if (num_sides == 4 && sumAngles == 360. && a == c && b == d &&
            A == C && B == D) {
            return true;
        }
        else { return false; }
    }

    Quadrangle_PrllGrmm::Quadrangle_PrllGrmm(double a, double b, double A, double B) : Quadrangle(a, b, c, d, A, B, C, D)
    {
        sides_count = 4; name = "Параллелограмм";
        c = Quadrangle::a; d = Quadrangle::b;
        C = Quadrangle::A; D = Quadrangle::B;
    }


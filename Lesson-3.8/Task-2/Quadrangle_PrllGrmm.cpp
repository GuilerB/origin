#include "Quadrangle_PrllGrmm.h"
#include "FigureCreationExc.h"

    Quadrangle_PrllGrmm::Quadrangle_PrllGrmm() :Quadrangle_PrllGrmm(a, b, A, B) {
        if (a != c || b != d) { throw FigureCreationError("������ �������� ������. �������: ������� 'a' � 'c' ��� 'd' � 'b' �� �����"); }
        if (A != C || B != D) { throw FigureCreationError("������ �������� ������. �������: ���� 'A' � 'C' ��� 'B' � 'D' �� �����"); }
    }

    void Quadrangle_PrllGrmm::print_info()  {
        Figure::print_info();
        std::cout << "(c������ " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << ", " << get_side_d() << "; ";
        std::cout << "���� " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ", " << get_angle_D() << ") ";
        std::cout << "������" << std::endl;
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
        sides_count = 4; name = "��������������";
        c = Quadrangle::a; d = Quadrangle::b;
        C = Quadrangle::A; D = Quadrangle::B;
    }


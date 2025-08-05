#include "Triangle_equalAllSides.h"
#include "FigureCreationExc.h"

    Triangle_equalAllSides::Triangle_equalAllSides() :Triangle_equalAllSides(a) {
        double sum = A + B + C;
        if (a != b || c != a || c != b) { throw FigureCreationError("������ �������� ������. �������: ������� �� �����"); }
        if (A != B || C != A || C != B) { throw FigureCreationError("������ �������� ������. �������: ���� �� �����"); }
        if (A != 60 || B != 60 || C != 60) { throw FigureCreationError("������ �������� ������. �������: ���� �� ����� �� ����� 60"); }
        if (sum != 180) {
            throw FigureCreationError("������ �������� ������. �������: ����� ����� �� ����� 180");
        }
        if (sides_count != 3) {
            throw FigureCreationError("������ �������� ������. �������: ���������� ������ �� ����� 3");
        }
    }

    void Triangle_equalAllSides::print_info() {
        Figure::print_info();
        std::cout << "(c������ " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << "; ";
        std::cout << "���� " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ") ";
        std::cout << "������" << std::endl;
    }
    bool Triangle_equalAllSides::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C;
        if (num_sides == 3 && sumAngles == 180. && c == a && c == b && A == C && C == B) { return true; }
        else { return false; }
    }

    Triangle_equalAllSides::Triangle_equalAllSides(double a) : Triangle(a, b, c, A, B, C)
    {
        sides_count = 3; name = "�������������� �����������";
        A = 60.0;
        c = Triangle::a; b = Triangle::a;
        C = A; B = A;
    }


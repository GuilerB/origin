//#include <iostream>
#include "Triangle_90deg.h"
#include "FigureCreationExc.h"

Triangle_90deg::Triangle_90deg() : Triangle_90deg(a, b, c, A, B) {
        double sum = A + B + C;
        if (C != 90) {
            throw FigureCreationError("������ �������� ������. �������: ���� C �� ����� 90");
        }
        if (sum != 180) {
            throw FigureCreationError("������ �������� ������. �������: ����� ����� �� ����� 180");
        }
        if (sides_count != 3) {
            throw FigureCreationError("������ �������� ������. �������: ���������� ������ �� ����� 3");
        }
    }

    void Triangle_90deg::print_info() {
        Figure::print_info();
        std::cout << "(c������ " << get_side_a() << ", " << get_side_b() << ", " << get_side_c() << "; ";
        std::cout << "���� " << get_angle_A() << ", " << get_angle_B() << ", " << get_angle_C() << ") ";
        std::cout << "������" << std::endl;
    }
    bool Triangle_90deg::check() {
        int num_sides = get_sides_count();
        double sumAngles = A + B + C;
        double angleC = C;
        if (num_sides == 3 && sumAngles == 180. && angleC == 90.) { return true; }
        else { return false; }
    }

    Triangle_90deg::Triangle_90deg(double a, double b, double c, double A, double B) : Triangle(a, b, c, A, B, C)
    {
        sides_count = 3; name = "������������� �����������";
        C = 90;
    }


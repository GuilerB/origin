#include <iostream>

class Figure
{

public:
    int get_sides_count() { return sides_count; };
    std::string get_name() { return name; };

    virtual double get_side_a() { return a; };
    virtual double get_side_b() { return b; };
    virtual double get_side_c() { return c; };
    virtual double get_side_d() { return d; };
    virtual double get_angle_A() { return A; };
    virtual double get_angle_B() { return B; };
    virtual double get_angle_C() { return C; };
    virtual double get_angle_D() { return D; };

    Figure() { sides_count = 0; name = "Фигура"; }
protected:
    int sides_count;
    std::string name;

    double a{ 0 }, b{ 0 }, c{ 0 }, d{ 0 }, A{ 0 }, B{ 0 }, C{ 0 }, D{ 0 };
};

class Triangle : public Figure
{
public:
    double get_side_a() override { return a; };
    double get_side_b() override { return b; };
    double get_side_c() override { return c; };
    double get_angle_A() override { return A; };
    double get_angle_B() override { return B; };
    double get_angle_C() override { return C; };

    Triangle() :Triangle(a, b, c, A, B, C) {}
protected:
    double a{ 1 }, b{ 2 }, c{ 3 }, A{ 10 }, B{ 15 }, C{ 135 };

    Triangle(double a, double b, double c, double A, double B, double C)
    {
        sides_count = 3; name = "Треугольник";
    }
};

class Quadrangle : public Figure
{
public:
    double get_side_a() override { return a; };
    double get_side_b() override { return b; };
    double get_side_c() override { return c; };
    double get_side_d() override { return d; };
    double get_angle_A() override { return A; };
    double get_angle_B() override { return B; };
    double get_angle_C() override { return C; };
    double get_angle_D() override { return D; };

    Quadrangle() : Quadrangle(a, b, c, d, A, B, C, D) {}

protected:
    double a{ 10 }, b{ 30 }, c{ 50 }, d{ 15 }, A{ 15 }, B{ 35 }, C{ 150 }, D{ 130 };

    Quadrangle(double a, double b, double c, double d, double A, double B, double C, double D)
    {
        sides_count = 4; name = "Четырехугольник";
    }
};

class Triangle_90deg : public Triangle
{
public:
    Triangle_90deg() : Triangle_90deg(a, b, c, A, B) {}
protected:
    Triangle_90deg(double a, double b, double c, double A, double B) : Triangle(a, b, c, A, B, C)
    {
        sides_count = 3; name = "Прямоугольный треугольник";
        C = 90;
    }
};

class Triangle_equal2sides : public Triangle
{
public:
    Triangle_equal2sides() : Triangle_equal2sides(a, b, A, B) {}
protected:
    Triangle_equal2sides(double a, double b, double A, double B) : Triangle(a, b, c, A, B, C)
    {
        sides_count = 3; name = "Равнобедренный треугольник";
        c = Triangle::a; C = Triangle::A;
    }
};

class Triangle_equalAllSides : public Triangle
{
public:
    Triangle_equalAllSides() :Triangle_equalAllSides(a) {}
protected:
    Triangle_equalAllSides(double a) : Triangle(a, b, c, A, B, C)
    {
        sides_count = 3; name = "Равносторонний треугольник";
        A = 60.0;
        c = Triangle::a; b = Triangle::a;
        C = A; B = A;
    }
};

class Quadrangle_PrllGrmm : public Quadrangle
{
public:
    Quadrangle_PrllGrmm() :Quadrangle_PrllGrmm(a, b, A, B) {}
protected:
    Quadrangle_PrllGrmm(double a, double b, double A, double B) : Quadrangle(a, b, c, d, A, B, C, D)
    {
        sides_count = 4; name = "Параллелограмм";
        c = Quadrangle::a; d = Quadrangle::b;
        C = Quadrangle::A; D = Quadrangle::B;
    }
};

class Quadrangle_PrUg : public Quadrangle_PrllGrmm
{
public:
    Quadrangle_PrUg() : Quadrangle_PrUg(a, b) {}
protected:
    Quadrangle_PrUg(double a, double b) : Quadrangle_PrllGrmm(a, b, A, B)
    {
        sides_count = 4; name = "Прямоугольник";
        A = 90.0;
        c = Quadrangle_PrllGrmm::a; d = Quadrangle_PrllGrmm::b;
        C = A; B = A; D = A;
    }
};

class Square : public Quadrangle_PrUg
{
public:
    Square() :Square(a) {}
protected:
    Square(double a) : Quadrangle_PrUg(a, b)
    {
        sides_count = 4; name = "Квадрат";
        c = Quadrangle_PrUg::a; d = Quadrangle_PrUg::a; b = Quadrangle_PrUg::a;
        C = Quadrangle_PrUg::A; B = Quadrangle_PrUg::A; D = Quadrangle_PrUg::A;
    }
};

class Romb : public Quadrangle_PrllGrmm
{
public:
    Romb() : Romb(a, A, B) {}
protected:
    Romb(double a, double A, double B) : Quadrangle_PrllGrmm(a, b, A, B)
    {
        sides_count = 4; name = "Ромб";
        c = Quadrangle_PrllGrmm::a; d = Quadrangle_PrllGrmm::a; b = Quadrangle_PrllGrmm::a;
        C = Quadrangle_PrllGrmm::A; D = Quadrangle_PrllGrmm::B;
    }
};

void print_info(Figure* obj) {

    if (obj->get_side_d() == 0.) {
        std::cout << obj->get_name() << ": " << std::endl;
        std::cout << "Стороны: " << "a=" << obj->get_side_a() << " b=" << obj->get_side_b() << " c=" << obj->get_side_c() << std::endl;
        std::cout << "Углы: " << "A=" << obj->get_angle_A() << " B=" << obj->get_angle_B() << " C=" << obj->get_angle_C() << std::endl;
        std::cout << "\n";
    }
    else {
        std::cout << obj->get_name() << ": " << std::endl;
        std::cout << "Стороны: " << "a=" << obj->get_side_a() << " b=" << obj->get_side_b() << " c=" << obj->get_side_c() << " d=" << obj->get_side_d() << std::endl;
        std::cout << "Углы: " << "A=" << obj->get_angle_A() << " B=" << obj->get_angle_B() << " C=" << obj->get_angle_C() << " D=" << obj->get_angle_D() << std::endl;
        std::cout << "\n";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли

    std::cout << "\n";

    Triangle triangle;
    Quadrangle quadrangle;

    Triangle_90deg tri_90deg;
    Triangle_equal2sides tri_EqSides;
    Triangle_equalAllSides tri_EqAllSides;

    Quadrangle_PrllGrmm quad_PrllGrm;
    Quadrangle_PrUg quad_PrUg;
    Square quad_Square;
    Romb quad_Romb;

    print_info(&triangle);
    print_info(&tri_90deg);
    print_info(&tri_EqSides);
    print_info(&tri_EqAllSides);

    print_info(&quadrangle);
    print_info(&quad_PrllGrm);
    print_info(&quad_PrUg);
    print_info(&quad_Square);
    print_info(&quad_Romb);

}
#pragma once
#include <iostream>
#include "Figure.h"

class Triangle : public Figure
{
public:
    double get_side_a() override ;
    double get_side_b() override ;
    double get_side_c() override ;
    double get_angle_A() override ;
    double get_angle_B() override ;
    double get_angle_C() override ;

    void print_info() override; 

    bool check() override; 

    Triangle(); 

protected:
    double a{ 1 }, b{ 2 }, c{ 3 }, A{ 60 }, B{ 90 }, C{ 30 };

    Triangle(double a, double b, double c, double A, double B, double C);
    
};

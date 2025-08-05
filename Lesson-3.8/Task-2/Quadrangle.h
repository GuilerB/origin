#pragma once
#include <iostream>
#include "Figure.h"
#include "FigureCreationExc.h"

class Quadrangle : public Figure
{
public:
    double get_side_a() override ;
    double get_side_b() override ;
    double get_side_c() override ;
    double get_side_d() override ;
    double get_angle_A() override ;
    double get_angle_B() override ;
    double get_angle_C() override ;
    double get_angle_D() override ;

    void print_info() override;
   
    bool check() override;
    
    Quadrangle(); 

protected:
    double a{ 10 }, b{ 30 }, c{ 50 }, d{ 15 }, A{ 15 }, B{ 35 }, C{ 150 }, D{ 130 };

    Quadrangle(double a, double b, double c, double d, double A, double B, double C, double D);
    
};


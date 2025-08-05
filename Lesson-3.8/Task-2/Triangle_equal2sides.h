#pragma once
#include <iostream>
#include "Triangle.h"


class Triangle_equal2sides : public Triangle
{
public:
    Triangle_equal2sides(); 

    void print_info() override; 
    bool check() override;

protected:
    Triangle_equal2sides(double a, double b, double A, double B);
};

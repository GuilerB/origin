#pragma once
#include <iostream>
#include "Triangle.h"

class Triangle_90deg : public Triangle
{
public:
    Triangle_90deg(); 

    void print_info() override;
    bool check() override; 

protected:
    Triangle_90deg(double a, double b, double c, double A, double B);
};

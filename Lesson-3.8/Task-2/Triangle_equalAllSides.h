#pragma once
#include <iostream>
#include "Triangle.h"

class Triangle_equalAllSides : public Triangle
{
public:
    Triangle_equalAllSides();
    void print_info() override;
    bool check() override;

protected:
    Triangle_equalAllSides(double a);
};

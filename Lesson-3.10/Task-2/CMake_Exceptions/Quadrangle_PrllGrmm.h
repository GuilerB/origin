#pragma once
#include <iostream>
#include "Quadrangle.h"

class Quadrangle_PrllGrmm : public Quadrangle
{
public:
    Quadrangle_PrllGrmm(); 

    void print_info() override; 

    bool check() override;

protected:
    Quadrangle_PrllGrmm(double a, double b, double A, double B);
};

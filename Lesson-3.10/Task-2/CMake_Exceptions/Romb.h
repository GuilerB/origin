#pragma once
//#include <iostream>
#include "Quadrangle_PrllGrmm.h"

class Romb : public Quadrangle_PrllGrmm
{
public:
    Romb();

    void print_info() override;

    bool check() override;

    Romb(double a, double A, double B);
};

#pragma once
#include <iostream>
#include "Quadrangle_PrllGrmm.h"

class Quadrangle_PrUg : public Quadrangle_PrllGrmm
{
public:
    Quadrangle_PrUg(); 

    void print_info() override;
    bool check() override;

protected:
    Quadrangle_PrUg(double a, double b);
};

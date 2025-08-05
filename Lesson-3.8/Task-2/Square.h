#pragma once
#include <iostream>
#include "Quadrangle_PrUg.h"

class Square : public Quadrangle_PrUg
{
public:
    Square();

    void print_info() override;

    bool check() override;

protected:
    Square(double a);
};
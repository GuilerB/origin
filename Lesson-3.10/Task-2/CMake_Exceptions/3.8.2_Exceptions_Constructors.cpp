#include <iostream>
#include <stdexcept>
#include <exception>

#include "FigureCreationExc.h"
#include "Figure.h"
#include "Triangle.h"
#include "Quadrangle.h"
#include "Triangle_90deg.h"
#include "Triangle_equal2sides.h"
#include "Triangle_equalAllSides.h"
#include "Quadrangle_PrllGrmm.h"
#include "Quadrangle_PrUg.h"
#include "Square.h"
#include "Romb.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли

    std::cout << "\n";
 
    try {
        Triangle triangle;
        Figure* tri_figure = &triangle;
        tri_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    catch (...) {
        std::cerr << "Произошло неизвестное исключение." << std::endl;
    }
    std::cout << "\n";

    try {
        Triangle_90deg tri_90deg;
        Figure* tri90_figure = &tri_90deg;
        tri90_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";

    try {
        Triangle_equal2sides tri_EqSides;
        Figure* triEqSides_figure = &tri_EqSides;
        triEqSides_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";

    try {
        Triangle_equalAllSides tri_EqAllSides;
        Figure* triAllEq_figure = &tri_EqAllSides;
        triAllEq_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";

    try {
        Quadrangle quadrangle;
        Figure* quad_figure = &quadrangle;;
        quad_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";

    try {
        Quadrangle_PrllGrmm quad_PrllGrm;
        Figure* quadPrllGrm_figure = &quad_PrllGrm;
        quadPrllGrm_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";

    try {
        Quadrangle_PrUg quad_PrUg;
        Figure* quadPrUg_figure = &quad_PrUg;
        quadPrUg_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";

    try {
        Square quad_Square;
        Figure* quadSq_figure = &quad_Square;
        quadSq_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";

    try {
        Romb quad_Romb;
        Figure* quadRo_figure = &quad_Romb;
        quadRo_figure->print_info();
    }
    catch (const FigureCreationError& e) { std::cerr << e.what() << std::endl; }
    std::cout << "\n";


}
#include <iostream>
#include "Figure.h"
   
    int Figure::get_sides_count() { return sides_count; };
    std::string Figure::get_name() { return name; };

    /*virtual*/ double Figure::get_side_a() { return a; };
    /*virtual*/ double Figure::get_side_b() { return b; };
    /*virtual*/ double Figure::get_side_c() { return c; };
    /*virtual*/ double Figure::get_side_d() { return d; };
    /*virtual*/ double Figure::get_angle_A() { return A; };
    /*virtual*/ double Figure::get_angle_B() { return B; };
    /*virtual*/ double Figure::get_angle_C() { return C; };
    /*virtual*/ double Figure::get_angle_D() { return D; };

    /*virtual*/ void Figure::print_info() {
        std::cout << get_name() << " ";
        /*if (check() == true) {
            std::cout << "Правильная" << std::endl;
        }
        else {
            std::cout << "Неправильная" << std::endl;
        }
        std::cout << "Количество сторон: " << get_sides_count() << std::endl;*/
    };

    /*virtual*/ bool Figure::check() {
        int num_sides = get_sides_count();
        if (num_sides == 0) { return true; }
        else { return false; }
    }

    Figure::Figure() { sides_count = 0; name = "Фигура"; }



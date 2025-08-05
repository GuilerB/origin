#pragma once
#include <iostream>

class Figure
{

public:
    int get_sides_count() ;
    std::string get_name() ;

    virtual double get_side_a() ;
    virtual double get_side_b() ;
    virtual double get_side_c() ;
    virtual double get_side_d() ;
    virtual double get_angle_A() ;
    virtual double get_angle_B() ;
    virtual double get_angle_C() ;
    virtual double get_angle_D() ;

    virtual void print_info();
    //{
    //    std::cout << get_name() << " ";
    //    /*if (check() == true) {
    //        std::cout << "Правильная" << std::endl;
    //    }
    //    else {
    //        std::cout << "Неправильная" << std::endl;
    //    }
    //    std::cout << "Количество сторон: " << get_sides_count() << std::endl;*/
    //};
    
    virtual bool check();

    Figure(); 

protected:
    int sides_count;
    std::string name;

    double a{ 0 }, b{ 0 }, c{ 0 }, d{ 0 }, A{ 0 }, B{ 0 }, C{ 0 }, D{ 0 };
};
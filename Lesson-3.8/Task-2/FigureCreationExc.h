#pragma once
#include <stdexcept>

class FigureCreationError : public std::domain_error
{
public:

    FigureCreationError(const std::string& msg);

};

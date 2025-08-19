#include "FigureCreationExc.h"

FigureCreationError::FigureCreationError(const std::string& msg) : std::domain_error(msg) {}



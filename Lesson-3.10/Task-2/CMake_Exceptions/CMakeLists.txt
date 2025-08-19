cmake_minimum_required(VERSION 3.22.0)

project(cmake_exceptions)

set(MY_HEADERS 
	Figure.h
	FigureCreationExc.h 
	Quadrangle.h 
	Quadrangle_PrllGrmm.h 
	Quadrangle_PrUg.h 
	Romb.h 
	Square.h 
	Triangle.h
	Triangle_equalAllSides.h 
	Triangle_equal2sides.h 
	triangle_90deg.h)

set(MY_SOURCES 
	3.8.2_Exceptions_Constructors.cpp
	Figure.cpp
	FigureCreationExc.cpp 
	Quadrangle.cpp 
	Quadrangle_PrllGrmm.cpp 
	Quadrangle_PrUg.cpp 
	Romb.cpp 
	Square.cpp 
	Triangle.cpp
	Triangle_equalAllSides.cpp 
	Triangle_equal2sides.cpp 
	triangle_90deg.cpp 
)

add_executable(cmake_exceptions ${MY_SOURCES} ${MY_HEADERS})
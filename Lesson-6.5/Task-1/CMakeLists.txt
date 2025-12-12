cmake_minimum_required(VERSION 3.20)

project(L6_T5_testing)

set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/18")

find_package(PostgreSQL REQUIRED)

add_executable(L6_T5_testing main.cpp)

add_subdirectory("C:/Program Files/libpqxx-7.10.4/libpqxx-7.10.4" libpqxx-build) # Укажите путь к libpq++

target_compile_features(L6_T5_testing PRIVATE cxx_std_17) # Включите C++17

target_link_libraries(L6_T5_testing pqxx)

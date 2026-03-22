cmake_minimum_required(VERSION 3.16)

project(StopwatchApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    main.cpp
    MainWindow.cpp
    Stopwatch.cpp
)

set(HEADERS
    MainWindow.h
    Stopwatch.h
)

set(UI_FILES
    MainWindow.ui
)

add_executable(StopwatchApp ${SOURCES} ${HEADERS} ${UI_FILES})

target_link_libraries(StopwatchApp Qt6::Core Qt6::Widgets)
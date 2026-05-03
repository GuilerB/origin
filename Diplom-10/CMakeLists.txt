cmake_minimum_required(VERSION 3.16)
project(SearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Sql Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Sql Widgets)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

add_library(database STATIC
    common/database.h
    common/database.cpp
    common/tokenizer.h
    common/tokenizer.cpp
)
target_include_directories(database PUBLIC ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(database PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
)

add_executable(indexer
    indexer/main_indexer.cpp
    indexer/indexer.h
    indexer/indexer.cpp
)
target_include_directories(indexer PRIVATE ${CMAKE_SOURCE_DIR}/indexer)
target_link_libraries(indexer PRIVATE database)

add_executable(searcher
    searcher/main_searcher.cpp
    searcher/searcherwindow.h
    searcher/searcherwindow.cpp
    searcher/searcherwindow.ui
)
target_include_directories(searcher PRIVATE ${CMAKE_SOURCE_DIR}/searcher)
target_link_libraries(searcher PRIVATE database Qt${QT_VERSION_MAJOR}::Widgets)

add_custom_command(TARGET indexer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        $<TARGET_FILE_DIR:indexer>/config.ini
)
add_custom_command(TARGET searcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        $<TARGET_FILE_DIR:searcher>/config.ini
)
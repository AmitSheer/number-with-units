cmake_minimum_required(VERSION 3.19)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-std=c++2a -Werror -Wsign-conversion)
add_executable(Demo Demo.cpp NumberWithUnits.hpp NumberWithUnits.cpp)
add_executable(test NumberWithUnits.hpp NumberWithUnits.cpp Test.cpp doctest.h)

cmake_minimum_required(VERSION 3.19)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp NumberWithUnits.hpp NumberWithUnits.cpp Test.cpp)
add_executable(Demo Demo.cpp NumberWithUnits.hpp NumberWithUnits.cpp)
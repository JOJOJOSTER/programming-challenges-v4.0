# CMakeList.txt : CMake project for SFML, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable(challenges "Unicode-Converter.cpp")

set_property(TARGET challenges PROPERTY CXX_STANDARD 17)
set_property(TARGET challenges PROPERTY CXX_STANDARD_REQUIRED ON)


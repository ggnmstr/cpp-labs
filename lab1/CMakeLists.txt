cmake_minimum_required(VERSION 3.21)

project(linkedhs VERSION 0.1)

add_executable(Lab1 main.cpp linkedhashset.cpp student.cpp)

add_compile_options(-Wall -Wpedantic -Werror -g)
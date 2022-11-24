cmake_minimum_required(VERSION 3.21)
project(forth_interpreter)

add_executable(interpret main.cpp commands.cpp)

SET(WARN_FLAGS "-Wall -Wpedantic -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}") 
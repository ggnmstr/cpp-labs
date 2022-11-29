cmake_minimum_required(VERSION 3.21)
project(forth_interpreter)

add_executable(interpret main.cpp interpreter.cpp commands.cpp)

SET(WARN_FLAGS "-Wall -Wpedantic -Wextra")

# https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} -fsanitize=address  -g ")
cmake_minimum_required(VERSION 3.21)
project(forth_interpreter)

add_executable(interpret main.cpp datastack.cpp interpreter.cpp commands.cpp)

set(WARN_FLAGS "-Wall -Wpedantic -Wextra")

set(CMAKE_CXX_STANDARD 14)

# https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} -fsanitize=address  -g ")
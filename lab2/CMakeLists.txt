cmake_minimum_required(VERSION 3.21)
project(forth_interpreter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(interpret main.cpp datastack.cpp interpreter.cpp commands.cpp)
add_executable(test_interpret datastack.cpp interpreter.cpp commands.cpp interpreter_test.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(WARN_FLAGS "-Wall -Wpedantic -Wextra")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} -fsanitize=address  -g ")


enable_testing()

target_link_libraries(
    test_interpret
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_interpret)


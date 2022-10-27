cmake_minimum_required(VERSION 3.21)

project(linkedhs VERSION 0.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(Lab1 main.cpp linkedhashset.hpp student.cpp)

#add_executable(linkedhs_test linkedhashset.hpp lhstest.cpp student.cpp)

# CR: remove line, check if options are still there
add_compile_options(-Wall -Wpedantic -Werror -g)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

SET(WARN_FLAGS "-Wall -Wpedantic -Wextra")
# CR: https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}") 

enable_testing()

target_link_libraries(
  linkedhs_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(linkedhs_test)
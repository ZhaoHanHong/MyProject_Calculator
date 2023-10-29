cmake_minimum_required(VERSION 3.9.1)

project(Calculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(MyLibrary STATIC src/arithmetic.cpp "include/calculator.h" "src/calculator.cpp")

add_executable(main main.cpp "include/calculator.h" "src/calculator.cpp")

target_link_libraries(main MyLibrary)

cmake_minimum_required(VERSION 3.6)
project(lab_14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp matrix.cpp matrix.h)
add_executable(lab_14 ${SOURCE_FILES})
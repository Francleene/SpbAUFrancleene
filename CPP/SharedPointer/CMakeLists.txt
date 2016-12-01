cmake_minimum_required(VERSION 3.6)
project(SharedPointer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp shared_ptr.cpp shared_ptr.h matrix.cpp matrix.h)
add_executable(SharedPointer ${SOURCE_FILES})
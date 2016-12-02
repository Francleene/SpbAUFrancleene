cmake_minimum_required(VERSION 3.6)
project(pthreads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall -Werror")

set(SOURCE_FILES main.c thread_pool.h thread_pool.c)
add_executable(pthreads ${SOURCE_FILES})
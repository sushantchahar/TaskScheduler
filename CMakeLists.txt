cmake_minimum_required(VERSION 4.2)
project(TaskScheduler)

set(CMAKE_CXX_STANDARD 20)

add_library(TaskScheduler STATIC library.cpp)

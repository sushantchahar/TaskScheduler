cmake_minimum_required(VERSION 3.20)
project(TaskScheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(taskscheduler STATIC src/Placeholder.cpp)
target_include_directories(taskscheduler PUBLIC include)

add_subdirectory(app)
add_subdirectory(tests)
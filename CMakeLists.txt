cmake_minimum_required(VERSION 3.20)
project(TaskScheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Interface target and its compiler specific options
add_library(taskscheduler_warnings INTERFACE)
target_compile_options(taskscheduler_warnings INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

add_library(taskscheduler STATIC
        src/Job.cpp
        include/taskscheduler/Job.h
        include/taskscheduler/JobId.h
        include/taskscheduler/JobState.h
        include/taskscheduler/JobStateRules.h
        src/JobStateRules.cpp)

target_include_directories(taskscheduler PUBLIC include)
target_link_libraries(taskscheduler PRIVATE taskscheduler_warnings)

# Introducing Google Test and CTest
include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.14.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_subdirectory(app)
add_subdirectory(tests)
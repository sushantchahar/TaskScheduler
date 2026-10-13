add_executable(taskscheduler_tests smoke_test.cpp
        JobIdTest.cpp
        JobStateTest.cpp
        JobTest.cpp)
target_link_libraries(taskscheduler_tests PRIVATE taskscheduler)
target_link_libraries(taskscheduler_tests PRIVATE taskscheduler GTest::gtest_main)
target_link_libraries(taskscheduler_tests PRIVATE taskscheduler_warnings)
include(GoogleTest)
gtest_discover_tests(taskscheduler_tests)
cmake_minimum_required(VERSION 3.0.0)
project(dictCompress VERSION 0.1.0)



find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(dictCompress main.cpp clean.cpp dictionary.cpp compress.cpp)
add_executable(test test.cpp)
target_link_libraries(test GTest::GTest GTest::Main)
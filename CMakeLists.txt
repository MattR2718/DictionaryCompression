cmake_minimum_required(VERSION 3.0.0)
project(dictCompress VERSION 0.1.0)

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Gnuplot REQUIRED)

add_executable(dictCompress main.cpp clean.cpp dictionary.cpp compress.cpp)
add_executable(test test.cpp clean.cpp dictionary.cpp compress.cpp)
add_executable(graph graph.cpp)

target_link_libraries(test GTest::GTest GTest::Main)
target_link_libraries(graph boost_iostreams boost_system boost_filesystem)
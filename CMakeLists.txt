cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

add_executable(tbb_1 tbb_example_1.cc)
target_link_libraries(tbb_1 tbb)

add_executable(tbb_2 tbb_example_2.cc)
target_link_libraries(tbb_2 tbb)


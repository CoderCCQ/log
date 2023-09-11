cmake_minimum_required(VERSION 3.5)

project(example LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test test.cpp)
target_link_libraries(test log)



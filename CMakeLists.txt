cmake_minimum_required(VERSION 3.23)
project(northengine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(northengine_lang)
add_subdirectory(northengine)

add_executable(northengine main.cpp)

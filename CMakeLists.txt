cmake_minimum_required (VERSION 2.8)
project (CuriosityGraphicsBase)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

INCLUDE_DIRECTORIES(./include)
add_subdirectory(./src)

cmake_minimum_required (VERSION 2.8)
project (CuriosityGraphicsBase)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")
SET(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib/")

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/src/")
link_directories("${PROJECT_SOURCE_DIR}/lib")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g")

#INCLUDE_DIRECTORIES(./include)
add_subdirectory(./src)
add_subdirectory(./test)
add_subdirectory(./game/breakout/src)

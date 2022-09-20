cmake_minimum_required(VERSION 3.1.0)
set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_C_COMPILER "gcc" )
project(operations_to_deals)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(operations_to_deals run.cpp)

add_subdirectory(tools)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(test_deals_processer tests/test.cpp)
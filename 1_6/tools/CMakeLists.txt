cmake_minimum_required(VERSION 3.1)
project(ToolsLib)

set(SOURCE_LIB tools.cpp)
add_library(Tools SHARED ${SOURCE_LIB})
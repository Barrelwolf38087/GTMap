cmake_minimum_required(VERSION 3.17)
project(GTMR)

set(CMAKE_CXX_STANDARD 17)

add_library(GTMR STATIC "")
target_include_directories(GTMR PUBLIC include PRIVATE src)

add_subdirectory(src)

cmake_minimum_required(VERSION 3.2)
project(playlist_creator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(playlist_creator ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.20)
project(cpp_lab3_remastered)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_lab3_remastered g-model.h g-model.cpp main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O4")

set(Boost_INCLUDE_DIR C:/SpecialMinGW/MinGW/include/)
set(Boost_LIBRARY_DIR C:/SpecialMinGW/MinGW/lib/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
cmake_minimum_required(VERSION 3.20)
project(lab6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O4")

set(Boost_INCLUDE_DIR C:/SpecialMinGW/MinGW/include/)
set(Boost_LIBRARY_DIR C:/SpecialMinGW/MinGW/lib/)
include_directories(${Boost_INCLUDE_DIR})

add_executable(lab6 main.cpp g.h g.cpp rsa.h big_int.h BigInt.h bigrsa.h)

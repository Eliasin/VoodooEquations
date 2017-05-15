cmake_minimum_required(VERSION 3.7)
project(DT3)

set(CMAKE_CXX_STANDARD 14)


file(GLOB_RECURSE INCLUDE_DEPENDENCIES
        "include/boost/spirit/include/*.hpp"
        "include/boost/fusion/include/*.hpp"
        "include/boost/phoenix/include/*.hpp"
        )

file(GLOB INCLUDE_DEPENDENCIES
        "include/boost/*.hpp"
        )

set(SOURCE_FILES main.cpp)

include_directories(include)

add_executable(DT3 ${SOURCE_FILES} ${INCLUDE_DEPENDENCIES})
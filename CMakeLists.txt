#! CMakeLists

cmake_minimum_required(VERSION 2.8)

project(SIMDMath)

set(CMAKE_CXX_FLAGS "-Wall -march=native")

# Debug options write here
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Release options write here
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(NOT CMAKE_BUILD_TYPE)
message (STATUS "build type is not specified. Set to Release")
set(CMAKE_BUILD_TYPE "RELEASE")
endif(NOT CMAKE_BUILD_TYPE)

message (STATUS "Configuring for ${CMAKE_BUILD_TYPE}...")

set(TARGET simdmath)
file (GLOB SRC *.cpp)

add_library(${TARGET} STATIC ${SRC})

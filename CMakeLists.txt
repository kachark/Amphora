
# configure dependencies and output paths

cmake_minimum_required(VERSION 2.8)

# Project's name
project(Amphora)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(BINARY_DIR "${PROJECT_SOURCE_DIR}/bin")

find_package(Boost 1.63 COMPONENTS filesystem date_time REQUIRED)
find_package(CryptoPP REQUIRED)


# make header files accessible to the compiler
include_directories(${INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

# instruct cmake to inspect these subfolders
add_subdirectory(${SOURCE_DIR})
# add_subdirectory(test) for unit_tests


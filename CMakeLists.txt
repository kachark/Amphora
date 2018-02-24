
# configure dependencies and output paths

cmake_minimum_required(VERSION 3.0)

#execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "environment")
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableNames ${_variableNames})
#  message(STATUS "${_variableNames}=${${_variableNames}}")
#endforeach()

set(CMAKE_CXX_STANDARD 11)

# Project's name
project(Amphora)

message("system: ${CMAKE_SYSTEM_PREFIX_PATH}")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
set(BINARY_DIR  "${PROJECT_SOURCE_DIR}/bin")

find_package(Boost 1.64 COMPONENTS filesystem date_time REQUIRED)
find_library(CRYPTOPP cryptopp)
message("cryptopp: ${CRYPTOPP}")


# make header files accessible to the compiler
include_directories(${INCLUDE_DIR})
include_directories("${LIB_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

# instruct cmake to inspect these subfolders
add_subdirectory(${SOURCE_DIR})
# add_subdirectory(test) for unit_tests

set(CMAKE_EXPORT_COMPILE_COMMANDS=ON )

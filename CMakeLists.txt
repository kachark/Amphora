# specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(amphora)

# Version number of the build
#set(amphora_VERSION_MAJOR 1)
#set(amphora_VERSION_MINOR 0)

# Set the output folder where your program will be created
# basically sets variables containing these paths
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

# link boost libraries
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.58.0 COMPONENTS date_time)	 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(amphora amphora.cpp account_util.cpp) 
    target_link_libraries(amphora ${Boost_LIBRARIES})
endif()


add_executable(amphora ${PROJECT_SOURCE_DIR}/amphora.cpp)

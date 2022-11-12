cmake_minimum_required(VERSION 3.15)
project(tracey)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Doxygen)
if(Doxygen_FOUND)
  add_subdirectory(doc)
else()
  message(STATUS "Doxygen not found, not building docs")
endif()

add_executable(tracey src/tracey.cpp)
target_include_directories(tracey PRIVATE include/tracey)

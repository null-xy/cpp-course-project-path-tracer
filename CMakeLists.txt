cmake_minimum_required(VERSION 3.15)
project(Tracey VERSION 0.0.0 DESCRIPTION "The next generation path tracer")

# Guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

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


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

message(STATUS "Finding external libraries")
option(WITH_EIGEN "Use Eigen3 library" ON)
if(WITH_EIGEN)
  set(BUILD_TESTING OFF)
  find_package(Eigen3 3.4.0 REQUIRED)
  unset(BUILD_TESTING)
endif()
message(STATUS "Finding external libraries - done")

find_package(Threads)

option(BUILD_DOCUMENTATION "Build documentation" ON)

if(BUILD_DOCUMENTATION)
message(STATUS "Building documentation")
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(doc)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

add_library(Tracey INTERFACE)
target_include_directories(Tracey INTERFACE include/tracey)
target_link_libraries(Tracey INTERFACE Threads::Threads)

if(WITH_EIGEN)
  target_link_libraries(Tracey INTERFACE Eigen3::Eigen)
endif()

add_executable(tracey src/tracey.cpp)
target_link_libraries(tracey PRIVATE Tracey)

option(BUILD_EXAMPLES "Build examples" ON)

if(BUILD_EXAMPLES)
  message(STATUS "Building examples")
  add_subdirectory(examples)
endif()

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
  message(STATUS "Building tests")
  include(CTest)
  add_subdirectory(tests)
endif()

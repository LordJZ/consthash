
cmake_minimum_required(VERSION 2.6)
project(consthashtests)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -lpthread" )

include_directories("${PROJECT_SOURCE_DIR}/dep")
include_directories("${PROJECT_SOURCE_DIR}/dep/cityhash")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(gtest dep/gtest/gtest-all.cc dep/gtest/gtest_main.cc)
add_library(rtfuncs dep/crc32.c dep/crc64.c)
add_library(cityhash dep/cityhash/city.cc)

add_executable(consthashtests
    tests/crc32.cxx
    tests/crc64.cxx
    tests/city.cxx
    tests/city64.cxx
    )

target_link_libraries(consthashtests gtest rtfuncs cityhash)

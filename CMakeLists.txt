cmake_minimum_required(VERSION 3.5)
project(FileIndex)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Log)
include_directories(Log/include)

include_directories(include)

option(BUILD_DOCS "Generate Docs" OFF)
if(BUILD_DOCS)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/docs)
endif()

if (BUILD_TESTS)
	enable_testing(true)
	add_subdirectory(Log/googletest)
	add_subdirectory(tests)
	add_definitions(-DDEBUG)
endif()

file(GLOB_RECURSE HEADERS "include/**.h")
file(GLOB_RECURSE CXXSOURCES "src/**.cpp")

add_library(fileindex ${HEADERS} ${CXXSOURCES})

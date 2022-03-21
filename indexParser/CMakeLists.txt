cmake_minimum_required(VERSION 3.5)

project(IndexParser)

include_directories(include)
include_directories(../include)
include_directories(../Log/include)

if (CMAKE_BUILD_TYPE)
	if (CMAKE_BUILD_TYPE MATCHES Debug)
		message("Building in debug mode, performance will lower (2x indexing time) and more verbose!")
		add_definitions(-DDEBUG)
	endif()
endif()

file (GLOB_RECURSE CXX_SOURCES "src/**.cpp")
file (GLOB_RECURSE HEADERS "include/**.h")

add_library(indexparser ${HEADERS} ${CXX_SOURCES})
target_compile_features(indexparser PRIVATE cxx_std_17)
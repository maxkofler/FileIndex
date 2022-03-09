cmake_minimum_required(VERSION 3.5)

project(Indexer)

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

add_library(indexer ${HEADERS} ${CXX_SOURCES})
target_compile_features(indexer PRIVATE cxx_std_17)

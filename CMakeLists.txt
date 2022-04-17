cmake_minimum_required(VERSION 3.5)
project(FileIndex)

add_subdirectory(Log)

if (CMAKE_BUILD_TYPE)
	if (CMAKE_BUILD_TYPE MATCHES Debug)
		enable_testing(true)
		add_subdirectory(Log/googletest)
		add_subdirectory(tests)
		add_definitions(-DDEBUG)
	endif()
endif()

file(GLOB_RECURSE HEADERS "include/**.h")
file(GLOB_RECURSE CXXSOURCES "src/**.cpp")

add_library(fileindex ${HEADERS} ${CXXSOURCES})

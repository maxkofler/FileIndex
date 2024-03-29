cmake_minimum_required(VERSION 3.5)
project(FileIndex)

add_subdirectory(sqlite3-cmake)

include_directories(include)
include_directories(sqlite3-cmake/src)

file(GLOB_RECURSE HEADERS "include/**.h")
file(GLOB_RECURSE CXXSOURCES "src/**.cpp")

add_library(fileindex ${HEADERS} ${CXXSOURCES})
target_link_libraries(fileindex log sqlite3)

option(FILEINDEX_TESTS "Build FileIndex tests" OFF)

if (FILEINDEX_TESTS)
	set(LOG_MAXLEVEL 20 CACHE STRING "Set the maximum log level")
endif()

include_directories(../Log/include)

if (FILEINDEX_TESTS)
	enable_testing()
	message("[FileIndex INFO] Building FileIndex tests...")
	add_subdirectory(googletest)
	add_subdirectory(tests)
	target_compile_definitions(fileindex PUBLIC DEBUG)
endif()

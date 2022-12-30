cmake_minimum_required(VERSION 3.5)
project(FileIndex)

find_package(SQLite3)

include_directories(include)
include_directories(${SQLite3_INCLUDE_DIRS})

file(GLOB_RECURSE HEADERS "include/**.h")
file(GLOB_RECURSE CXXSOURCES "src/**.cpp")

add_library(fileindex ${HEADERS} ${CXXSOURCES})
target_link_libraries(fileindex log ${SQLite3_LIBRARIES})

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

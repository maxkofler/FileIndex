cmake_minimum_required(VERSION 3.5)
project(FileIndex)

include_directories(include)

file(GLOB_RECURSE HEADERS "include/**.h")
file(GLOB_RECURSE CXXSOURCES "src/**.cpp")

add_library(fileindex ${HEADERS} ${CXXSOURCES})

include_directories(../Log/include)

if (LOG_PROFILE)
	target_compile_definitions(fileindex PUBLIC "LOG_ENABLE_PROFILING")
endif()

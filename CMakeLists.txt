cmake_minimum_required(VERSION 3.5)
project(FileIndex)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(fileindex)

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
	add_subdirectory(fileindex/tests)
	target_compile_definitions(fileindex PUBLIC "DEBUG" PUBLIC "LOG_ENABLE_PROFILING")
endif()

if (LOG_PROFILE)
	target_compile_definitions(fileindex PUBLIC "LOG_ENABLE_PROFILING")
endif()

include_directories(cliapp/include)
include_directories(fileindex/include)
file(GLOB_RECURSE CLI_CXX_SOURCES "cliapp/src/**.cpp")

add_executable(fileindexcli ${CLI_CXX_SOURCES})

target_link_libraries(fileindexcli log fileindex)

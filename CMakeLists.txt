cmake_minimum_required(VERSION 3.5)
project(FileIndex)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(Log/include)
include_directories(cliapp/include)
include_directories(fileindex/include)

add_subdirectory(Log)
add_subdirectory(fileindex)

option(BUILD_DOCS "Generate Docs" OFF)
if(BUILD_DOCS)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/docs)
endif()

if (CMAKE_BUILD_TYPE)
	if (CMAKE_BUILD_TYPE MATCHES Debug)
		add_definitions(-DDEBUG)
	endif()
endif()

file(GLOB_RECURSE CLI_CXX_SOURCES "cliapp/src/**.cpp")

add_executable(fileindexcli ${CLI_CXX_SOURCES})

target_link_libraries(fileindexcli log fileindex)

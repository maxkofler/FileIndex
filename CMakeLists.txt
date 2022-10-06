cmake_minimum_required(VERSION 3.5)
project(FileIndex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(ADDITIONAL_LIBRARIES "")

include_directories(cliapp/include)
include_directories(fileindex/include)

include_directories(Log/include)
include_directories(NamesDB/include)

include_directories(args)

set(LOG_MAXLEVEL 12 CACHE STRING "Set the maximum log level")
set(LOG_NOCHECK ON CACHE BOOL "Disable Log checks")
set(LOG_NOMUTEX ON CACHE BOOL "Disable Log mutexes")

add_subdirectory(Log)
add_subdirectory(fileindex)
add_subdirectory(NamesDB)

if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
	message("Forcing the GNU compiler to link against stdc++fs")
	set(ADDITIONAL_LIBRARIES ${LEAF_ADDITIONAL_LIBRARIES} stdc++fs)
endif()

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

target_link_libraries(fileindexcli log fileindex ${ADDITIONAL_LIBRARIES})

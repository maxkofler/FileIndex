cmake_minimum_required(VERSION 3.5)

project(FileIndexCLI)

include_directories(include)

file(GLOB_RECURSE CXX_SOURCES "src/**.cpp")

add_executable(fileindexcli ${CXX_SOURCES})

target_link_libraries(fileindexcli fileindex log)

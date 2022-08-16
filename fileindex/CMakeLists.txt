cmake_minimum_required(VERSION 3.5)
project(FileIndex)

include_directories(include)

file(GLOB_RECURSE HEADERS "include/**.h")
file(GLOB_RECURSE CXXSOURCES "src/**.cpp")

add_library(fileindex ${HEADERS} ${CXXSOURCES})
target_link_libraries(fileindex log)

include_directories(../Log/include)

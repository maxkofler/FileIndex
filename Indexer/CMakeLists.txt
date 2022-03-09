cmake_minimum_required(VERSION 3.5)

project(Indexer)

include_directories(include)
include_directories(../Log/include)

file (GLOB_RECURSE CXX_SOURCES "src/**.cpp")
file (GLOB_RECURSE HEADERS "include/**.h")

add_library(indexer ${HEADERS} ${CXX_SOURCES})

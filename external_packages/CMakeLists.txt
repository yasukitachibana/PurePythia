cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project (libExternal)

#for MacOSX
cmake_policy(SET CMP0042 NEW)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../lib/")

set (SOURCES
    tinyxml2.cc
)

add_library(PurePythiaExternal SHARED ${SOURCES})

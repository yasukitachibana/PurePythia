cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project (libPurePythia)

#for MacOSX
cmake_policy(SET CMP0042 NEW)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "./lib")


FILE(GLOB sourcefiles *.cc)
set (SOURCES  ${SOURCES}  ${sourcefiles} )

# framework
# FILE(GLOB frameworksources framework/*.cc)
# set (SOURCES  ${SOURCES}  ${frameworksources} )




#######################################
add_library(PurePythia SHARED ${SOURCES})
target_link_libraries (PurePythia PurePythiaExternal ${PYTHIA8_LIBRARIES})
# -------------------------------------------------------------------------

# -*- mode: cmake; -*-

## CMake pre-settings
cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

############################################################
## Project setup
project(WaveDump C)
set(WaveDump_VERSION_MAJOR    1)
set(WaveDump_VERSION_MINOR    6)
set(WaveDump_VERSION_REVISION 1)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH     ${PROJECT_BINARY_DIR}/lib)

## install dirs
if(NOT DEFINED INSTALL_LIBEXECDIR)
  message(STATUS "Set default libexec as prefix")
  set(INSTALL_LIBEXECDIR "${CMAKE_INSTALL_PREFIX}")
endif(NOT DEFINED INSTALL_LIBEXECDIR)
# datadir = ${libexec}/share or ${prefix}/share/WaveDump
if(NOT DEFINED INSTALL_DATADIR)
  set(INSTALL_DATADIR "${CMAKE_INSTALL_PREFIX}/share/WaveDump")
endif(NOT DEFINED INSTALL_DATADIR)

############################################################
# Libraries

if(NOT DEFINED CAEN_LIB_PATH)
  message(STATUS "Set default CAEN Libraries path")
  set(CAEN_LIB_PATH "${INSTALL_LIBEXECDIR}/lib")
endif(NOT DEFINED CAEN_LIB_PATH)
if(NOT DEFINED CAEN_INCLUDE_PATH)
  message(STATUS "Set default CAEN include path")
  set(CAEN_INCLUDE_PATH "${INSTALL_LIBEXECDIR}/include")
endif(NOT DEFINED CAEN_INCLUDE_PATH)

link_directories(${CAEN_LIB_PATH})
include_directories(${CAEN_INCLUDE_PATH})

# dependencies
include_directories(inc)

# compiling options
add_definitions(-DLINUX)

############################################################
# sources

# then .. WaveDump
add_subdirectory(src)

############################################################
# Install

install( FILES
  ChangeLog
  AUTHORS
  COPYING
  README
  Setup/WaveDumpConfig.txt
  DESTINATION
  ${INSTALL_DATADIR} )

install( DIRECTORY
  inc
  src
  DESTINATION ${INSTALL_DATADIR}/sources/ )


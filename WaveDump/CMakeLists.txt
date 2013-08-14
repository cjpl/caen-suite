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
# libdir = ${libexec}/lib
set(INSTALL_LIBDIR "${INSTALL_LIBEXECDIR}/lib")
# incdir = ${libexec}/include
if(NOT DEFINED INSTALL_INCLUDEDIR)
  set(INSTALL_INCLUDEDIR "${INSTALL_LIBEXECDIR}/include")
endif(NOT DEFINED INSTALL_INCLUDEDIR)
# datadir = ${libexec}/share or ${prefix}/share/WaveDump
if(NOT DEFINED INSTALL_DATADIR)
  set(INSTALL_DATADIR "${CMAKE_INSTALL_PREFIX}/share/WaveDump")
endif(NOT DEFINED INSTALL_DATADIR)
# docdir = ${prefix}/share/doc/WaveDump
if(NOT DEFINED INSTALL_DOCDIR)
  set(INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/share/doc/WaveDump")
endif(NOT DEFINED INSTALL_DOCDIR)

############################################################

# find libCAENVME
#link_directories(${CMAKE_SOURCE_DIR}/../VMELib/lib/x64)

# find_library(CAENVME_LIB CAENVME)
# if(CAENVME_LIB)
#   message(STATUS "Found ${CAENVME_LIB}")
# endif(CAENVME_LIB)

#find_library(CAENCOMM_LIB CAENComm)
#find_library(CAENDIGI_LIB CAENDigitizer)
#find_library(pthread)
#find_package(Threads)

# Add definitions
#add_definitions(-DLINUX -Wl,--allow-multiple-definition)
add_definitions(-DLINUX)

# dependencies
include_directories(inc)

############################################################
# sources

# then .. WaveDump
add_subdirectory(src)

############################################################
## install: headers
# install(DIRECTORY include/  DESTINATION ${INSTALL_INCLUDEDIR}/gppanel/)

## install: docs
# install(DIRECTORY WaveDump/docs/ DESTINATION ${INSTALL_DATADIR})
#install(FILES
#  WaveDump/licence.txt
#  WaveDump/readme.txt
#  WaveDump/MathplotMyModifications.txt
#  DESTINATION ${INSTALL_DATADIR})

# -*- mode: cmake; -*-

## CMake pre-settings
cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

############################################################
## Project setup
project(CAENScope CXX C)
set(CAENScope_VERSION_MAJOR    1)
set(CAENScope_VERSION_MINOR    6)
set(CAENScope_VERSION_REVISION 1)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH     ${PROJECT_BINARY_DIR}/lib)

## install dirs
if(NOT DEFINED INSTALL_LIBEXECDIR)
  message(STATUS "Set default libexec as prefix")
  set(INSTALL_LIBEXECDIR "${CMAKE_INSTALL_PREFIX}")
endif(NOT DEFINED INSTALL_LIBEXECDIR)
# datadir = ${libexec}/share or ${prefix}/share/CAENScope
if(NOT DEFINED INSTALL_DATADIR)
  set(INSTALL_DATADIR "${CMAKE_INSTALL_PREFIX}/share/CAENScope")
endif(NOT DEFINED INSTALL_DATADIR)

############################################################

# wxWidgets
find_package(wxWidgets)
IF(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  add_definitions(${wxWidgets_CXX_FLAGS})
ELSE(wxWidgets_FOUND)
  message(ERROR "Failed to find wxWidgets")
ENDIF(wxWidgets_FOUND)

## libraries
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

# find libCAENVME
#link_directories(${CMAKE_SOURCE_DIR}/../VMELib/lib/x64)

# find_library(CAENVME_LIB CAENVME)
# if(CAENVME_LIB)
#   message(STATUS "Found ${CAENVME_LIB}")
# endif(CAENVME_LIB)

# Add definitions
add_definitions(-DLINUX -Wl,--allow-multiple-definition -nostartfiles)
#add_definitions(-DLINUX)

# dependencies
include_directories(include DigitizerSDK/include)

############################################################
# sources
# build libCAENdigitizerSDK first
#add_subdirectory(../DigitizerSDK/src "${CMAKE_CURRENT_BINARY_DIR}/digiSDK")
add_subdirectory(DigitizerSDK/src)
# then .. CAENScope
add_subdirectory(src)

############################################################

# install: docs imgs
install( DIRECTORY
  doc img
  DESTINATION ${INSTALL_DATADIR} )

install( FILES
  ChangeLog
  AUTHORS
  COPYING
  README
  DESTINATION
  ${INSTALL_DATADIR} )


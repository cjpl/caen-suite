# -*- mode: cmake; -*-

## CMake pre-settings
cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/)

############################################################
## Project setup
project(CAENdigitizerSDK C)
set(CAENdigitizerSDK_VERSION_MAJOR    1)
set(CAENdigitizerSDK_VERSION_MINOR    3)
set(CAENdigitizerSDK_VERSION_REVISION 0)

############################################################

# find libCAENVME
link_directories(${CMAKE_SOURCE_DIR}/../VMELib/lib/x64)

include_directories(include ${CMAKE_SOURCE_DIR}/../VMELib/include)

# sources
add_subdirectory(src)

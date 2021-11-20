cmake_minimum_required(VERSION 3.7...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(bsf-lib
        VERSION 1.0
        DESCRIPTION "Basalt shared libraries between clients")

set(QT_LOCATION "" CACHE PATH "[Required] QT Location")
if (NOT QT_LOCATION)
    message(FATAL_ERROR "'QT_LOCATION' variable is required but was not set.")
else ()
    message(STATUS "Using QT at: ${QT_LOCATION}")
endif ()

set(CMAKE_PREFIX_PATH "${QT_LOCATION}")

#include(CTest)
#enable_testing()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add src directory
add_subdirectory(src)
add_subdirectory(apps/pavement)
#add_subdirectory(apps/scale)

#add_subdirectory(test)

cmake_minimum_required(VERSION 3.7...3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(bsf-scale
        VERSION 1.0
        DESCRIPTION "Bsf Weighstation app")

# BUILD OPTION
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add src directory
add_subdirectory(src)
add_subdirectory(app)

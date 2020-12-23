cmake_minimum_required(VERSION 3.7...3.18)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../src)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Network Sql REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(srcTestLib SHARED "")

    # TARGET SOURCES
    target_sources(srcTestLib
            PRIVATE
            autotest/AutoTest.cpp
            PUBLIC
            autotest/AutoTest.h
            )

    target_link_libraries(srcTestLib PUBLIC
            bsf
            Qt5::Core
            Qt5::Test
            Qt5::Widgets
            )

    add_subdirectory(domain)


else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

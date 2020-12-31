cmake_minimum_required(VERSION 3.7...3.18)
project(bsf-test
        VERSION 1.0
        DESCRIPTION "Tests for libraries and apps."
        )
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    add_subdirectory(domain)
    add_subdirectory(mqtt)
    add_subdirectory(parser)
    add_subdirectory(repo)
    add_subdirectory(ui)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

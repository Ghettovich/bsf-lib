cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets DBus Core Sql Network Mqtt REQUIRED)

if (Qt5Widgets_FOUND)

    # Create shared library for targetting sources
    add_library(bsfOperator SHARED "")

    target_link_libraries(bsfOperator PUBLIC
            bsf
            )

    target_include_directories(bsfOperator
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    # Add subdirectories
    add_subdirectory(ui)

    install(TARGETS bsfOperator DESTINATION include)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

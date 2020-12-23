cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            # MAIN
            main/MainWindow.h
            )

    # TARGET SOURCES
    target_sources(bsfWeightstationlib PRIVATE
            # UI FILES -- MAIN
            main/MainWindow.cpp
            main/mainwindow.ui
            # HEADER
            PUBLIC
            ${HEADER_LIST})

    target_link_libraries(bsfWeightstationlib PUBLIC
            Qt5::Widgets)

    target_include_directories(bsfWeightstationlib
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
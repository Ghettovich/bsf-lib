cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Core)

add_executable(PavementApp
        pavement.app.cpp
        pavement.controller.cpp
        pavement.controller.h
        mainwindow.ui
        mainwindow.cpp
        mainwindow.h
        settings.qrc)

target_link_libraries(PavementApp
        Qt5::Core
        Qt5::Widgets
        appservice
        domain
        service
        ui)

target_include_directories(PavementApp
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
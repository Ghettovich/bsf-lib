cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets)

add_executable(OperatorAppExe
        OperatorApp.cpp
        mainwindow.ui
        mainwindow.cpp
        mainwindow.h
        settings.qrc)

target_link_libraries(OperatorAppExe
        Qt5::Widgets
        appservice
        domain
        service
        ui)

target_include_directories(OperatorAppExe
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
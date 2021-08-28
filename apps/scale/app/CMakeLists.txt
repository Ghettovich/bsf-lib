cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ScaleAppExe
        ScaleApp.cpp
        mainwindow.ui
        MainWindow.cpp
        MainWindow.h)

target_link_libraries(ScaleAppExe
        Qt5::Widgets
        appservice
        domain
        service
        ui)

target_include_directories(ScaleAppExe
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
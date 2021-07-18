#cmake_minimum_required(VERSION 3.7...3.18)
#set(CMAKE_CXX_STANDARD 14)
#
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
## find Qt5 and required components | Qt5_DIR
#find_package(Qt5 COMPONENTS Network Widgets REQUIRED)
#
#set(HEADER_LIST
#        # MAIN
#        main/mainwindow.h
#        )
#
#target_sources(OperatorAppExe
#        PRIVATE
#        # MAIN
#        main/mainwindow.cpp
#        main/mainwindow.ui
#        ${HEADER_LIST})
#
#target_include_directories(OperatorAppExe
#        PUBLIC
#        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
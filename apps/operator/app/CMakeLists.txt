cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Mqtt)

add_executable(OperatorAppExe
        OperatorApp.cpp)

target_sources(OperatorAppExe
        PRIVATE
        settings.qrc)

target_link_libraries(OperatorAppExe
        bsfOperator
        Qt5::Mqtt
        Qt5::Widgets)
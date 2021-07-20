cmake_minimum_required(VERSION 3.13...3.18)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets DBus Core Sql Network Mqtt REQUIRED)

add_subdirectory(appservice)
add_subdirectory(domain)
add_subdirectory(service)
add_subdirectory(ui)


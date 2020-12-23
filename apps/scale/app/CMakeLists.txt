cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(../src)

add_executable(BsfWeightstationApp
        ScaleApp.cpp
        )

target_link_libraries(BsfWeightstationApp
        bsfWeightstationlib
        Qt5::Widgets
        )
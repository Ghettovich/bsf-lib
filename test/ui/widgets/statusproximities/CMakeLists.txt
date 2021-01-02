cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Mqtt REQUIRED)

enable_testing()

if (Qt5Widgets_FOUND)

    # ADD TEST EXECUTABLES
    add_executable(ProximityTreeWidgetTest
            tst_ProximityTreeWidgetStatus.cpp
            tst_ProximityTreeWidgetStatus.h
            ${CMAKE_CURRENT_SOURCE_DIR}/../../../resource/jsonPayload.qrc
            )

    target_link_libraries(ProximityTreeWidgetTest PRIVATE
            bsf
            Qt5::Test
            Qt5::Core
            Qt5::Mqtt
            Qt5::Widgets
            )

    target_include_directories(ProximityTreeWidgetTest PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    add_test(proximityTreeWidgetTest ProximityTreeWidgetTest)

    add_custom_command(
            TARGET ProximityTreeWidgetTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/bsf.db
            ${CMAKE_CURRENT_BINARY_DIR}/bsf.db
    )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
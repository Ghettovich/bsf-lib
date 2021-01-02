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
    add_executable(GroupBoxBeltFeedersTest
            tst_GroupBoxBeltFeeders.cpp
            tst_GroupBoxBeltFeeders.h
            ${CMAKE_CURRENT_SOURCE_DIR}/../../../resource/jsonPayload.qrc
            )

    target_link_libraries(GroupBoxBeltFeedersTest PRIVATE
            bsf
            Qt5::Test
            Qt5::Core
            Qt5::Mqtt
            Qt5::Widgets
            )

    target_include_directories(GroupBoxBeltFeedersTest PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    add_test(groupBoxBeltFeedersTest GroupBoxBeltFeedersTest)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
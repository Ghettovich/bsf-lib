cmake_minimum_required(VERSION 3.7...3.18)
project(bsf-test
        VERSION 1.0
        DESCRIPTION "Tests for libraries and apps."
        )
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(srcTestLib SHARED "")

    add_subdirectory(domain)
    add_subdirectory(mqtt)
    add_subdirectory(parser)
    add_subdirectory(repo)
    add_subdirectory(ui)

    # TARGET SOURCES
    add_executable(BsfTest
            autotest/AutoTest.cpp
            autotest/AutoTest.h
            resource/jsonPayload.qrc
            )

    target_link_libraries(BsfTest PUBLIC
            bsf
            srcTestLib
            Qt5::Core
            Qt5::Test
            )

    target_include_directories(BsfTest
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    add_custom_command(
            TARGET BsfTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/resource/database/bsf.db
            ${CMAKE_CURRENT_BINARY_DIR}/resource/database/bsf.db
    )

    add_test(NAME RecipeTest COMMAND BsfTest)
    add_test(NAME TransformPayloadTest COMMAND BsfTest)
    add_test(NAME ActionArduinoRepoTest COMMAND BsfTest)
    add_test(NAME ArduinoRepoTest COMMAND BsfTest)
    add_test(NAME IODeviceRepoTest COMMAND BsfTest)
    add_test(NAME LogRepoTest COMMAND BsfTest)
    add_test(NAME RecipeRepoTest COMMAND BsfTest)
    add_test(NAME StateCodeRepoTest COMMAND BsfTest)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

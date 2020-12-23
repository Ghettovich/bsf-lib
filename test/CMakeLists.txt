cmake_minimum_required(VERSION 3.7...3.18)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../src)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets Network Sql REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(srcTestLib SHARED "")

    add_subdirectory(domain)
    add_subdirectory(parser)
    add_subdirectory(repo)

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
            Qt5::Widgets
            )

    target_include_directories(BsfTest
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    install(TARGETS BsfTest
            EXPORT BsfTestTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    install(FILES srcTestLib DESTINATION include)

    install(EXPORT BsfTestTargets
            FILE BsfTestTargets.cmake
            NAMESPACE bsfTest::
            DESTINATION lib/cmake
            )

    add_custom_command(
            TARGET BsfTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/resource/database/bsf.db
            ${CMAKE_CURRENT_BINARY_DIR}/resource/database/bsf.db
    )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

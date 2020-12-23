cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            bsfdatabaseconfig.h
            )

    # TARGET MAIN LIB
    target_sources(bsf PRIVATE
            bsfdatabaseconfig.cpp
            # HEADER LIST
            PRIVATE
            ${HEADER_LIST}
            )

    # Linkes files with QT
    target_link_libraries(bsf
            PRIVATE
            Qt5::Core
            Qt5::Sql
            )

    # Define rules for exporting domain
    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

else (!Qt5Widgets_FOUND)
# OOPS
message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

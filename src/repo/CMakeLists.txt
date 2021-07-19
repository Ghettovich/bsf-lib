cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(AUTOGEN_TARGET_DEPENDS repo)

include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            actionarduinorepo.h
            arduinorepo.h
            iodevicerepo.h
            logrepo.h
            reciperepo.h
            statecoderepo.h
            )

    # TARGET SOURCES
    target_sources(bsf PRIVATE
            actionarduinorepo.cpp
            arduinorepo.cpp
            iodevicerepo.cpp
            logrepo.cpp
            reciperepo.cpp
            statecoderepo.cpp
            # HEADER LIST
            PRIVATE
            ${HEADER_LIST})

    # Linkes files with QT
    target_link_libraries(bsf
            PUBLIC
            Qt5::Core
            Qt5::Sql
            services)

    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

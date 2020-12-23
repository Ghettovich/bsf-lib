cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(AUTOGEN_TARGET_DEPENDS parser)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

if (Qt5Widgets_FOUND)

# HEADER LIST
    set(HEADER_LIST
            transformpayload.h)

    # TARGET SOURCES
    target_sources(bsf PRIVATE
            transformpayload.cpp
            # HEADERS LIST
            PRIVATE
            ${HEADER_LIST})

    # Linkes files with QT
    target_link_libraries(bsf
            PUBLIC
            Qt5::Core)

    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

else (!Qt5Widgets_FOUND)
# OOPS
message("could not find qt widgets")
endif (Qt5Widgets_FOUND)


cmake_minimum_required(VERSION 3.13...3.18)
set(project ui)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            action.h
            arduino.h
            bafalog.h
            component.h
            detectionsensor.h
            iodevice.h
            iodevicetype.h
            recipe.h
            relay.h
            statecode.h
            weightcensor.h
            )

    # TARGET SOURCES
    target_sources(bsf
            PRIVATE
            action.cpp
            arduino.cpp
            bafalog.cpp
            component.cpp
            detectionsensor.cpp
            iodevice.cpp
            iodevicetype.cpp
            recipe.cpp
            relay.cpp
            statecode.cpp
            weightcensor.cpp
            # WIDGET ENUM
            BsfWidgetEnum.h
            # HEADER LIST
            PRIVATE
            ${HEADER_LIST}
            )

    # Link files with QT
    target_link_libraries(bsf
            PUBLIC
            Qt5::Core
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

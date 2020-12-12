cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(AUTOGEN_TARGET_DEPENDS mqtt)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Mqtt REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            MqttClient.h
            MqttSubscription.h
            )

    # TARGET MAIN LIB
    target_sources(bsf PRIVATE
            MqttClient.cpp
            MqttSubscription.cpp
            # HEADER LIST
            PRIVATE
            ${HEADER_LIST}
            )

    # Linkes files with QT
    target_link_libraries(bsf
            PRIVATE
            Qt5::Mqtt
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

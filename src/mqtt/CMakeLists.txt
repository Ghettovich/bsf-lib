cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Needed for creating export
include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Mqtt REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            MqttClient.h
            MqttSubscription.h)

    # TARGET MAIN LIB
    add_library(mqttclient SHARED
            MqttClient.cpp
            MqttSubscription.cpp
            ${HEADER_LIST})

    # Set the property version pkconfig
    set_property(TARGET mqttclient PROPERTY VERSION 1.0)

    # Linkes files with QT
    target_link_libraries(mqttclient PUBLIC
            Qt5::Mqtt
            )

    # Define rules for exporting domain
    target_include_directories(mqttclient
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:include>")

    install(TARGETS mqttclient
            EXPORT mqttclientTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    # install header file
    install(FILES ${HEADER_FILES} DESTINATION include)

    install(EXPORT mqttclientTargets
            FILE mqttclientTargets.cmake
            NAMESPACE mqttclient::
            DESTINATION lib/cmake
            )

    install(TARGETS mqttclient DESTINATION lib)

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/mqttclientConfig.cmake"
            INSTALL_DESTINATION lib/cmake
            )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/mqttclientConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/mqttclientConfigVersion.cmake"
            DESTINATION lib/cmake
            )

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/mqttclientConfigVersion.cmake"
            VERSION "1.0"
            COMPATIBILITY AnyNewerVersion
    )

    export(EXPORT mqttclientTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/mqttclientTargets.cmake")

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

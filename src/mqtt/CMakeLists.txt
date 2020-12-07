cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(AUTOGEN_TARGET_DEPENDS mqtt)

# Needed for creating export
include(CMakePackageConfigHelpers)

#list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/src/")
#
##find_package(domain)
##
##add_library(domain SHARED IMPORTED)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Mqtt REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            MqttClient.h
            MqttSubscription.h
            )

    # TARGET MAIN LIB
    add_library(mqtt SHARED
            MqttClient.cpp
            MqttSubscription.cpp
            ${HEADER_LIST})

    # Set the property version pkconfig
    set_property(TARGET mqtt PROPERTY VERSION 1.0)

    # Linkes files with QT
    target_link_libraries(mqtt
            INTERFACE
            domain
            parser
            ui
            PRIVATE
            Qt5::Mqtt
            )

    # Define rules for exporting domain
    target_include_directories(mqtt
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:include/mqtt>"
            PRIVATE
            ${CMAKE_SOURCE_DIR}/src/domain
            ${CMAKE_SOURCE_DIR}/src/parser
            ${CMAKE_SOURCE_DIR}/src/ui/widgets/binloaddrop
            ${CMAKE_SOURCE_DIR}/src/ui/widgets/liftupdown
            )

    install(TARGETS mqtt
            EXPORT mqttTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    # install header file
    install(FILES ${HEADER_FILES} DESTINATION include)

    install(EXPORT mqttTargets
            FILE mqttTargets.cmake
            NAMESPACE mqtt::
            NAMESPACE mqtt::
            DESTINATION lib/cmake
            )

    install(TARGETS mqtt DESTINATION lib)

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/mqttConfig.cmake"
            INSTALL_DESTINATION lib/cmake
            )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/mqttConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/mqttConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mqtt
            )

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/mqttConfigVersion.cmake"
            VERSION "1.0"
            COMPATIBILITY AnyNewerVersion
    )

    export(EXPORT mqttTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/mqttTargets.cmake"
            NAMESPACE mqtt::)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

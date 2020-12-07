cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Needed for creating export
include(CMakePackageConfigHelpers)

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
            weightcensor.h)

    # TARGET SOURCES
    add_library(domain SHARED
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
            ${HEADER_LIST})

    # Set the property version pkconfig
    set_property(TARGET domain PROPERTY VERSION 1.0)

    # Link files with QT
    target_link_libraries(domain
            PRIVATE
            Qt5::Core)

    # Define rules for exporting domain
    target_include_directories(domain
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:include>")

    install(TARGETS domain
            EXPORT domainTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    # install header file
    install(FILES ${HEADER_FILES} DESTINATION include)

    install(EXPORT domainTargets
            FILE domainTargets.cmake
            NAMESPACE domain::
            DESTINATION lib/cmake
            )

    install(TARGETS domain DESTINATION lib)

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/domainConfig.cmake"
            INSTALL_DESTINATION lib/cmake
            )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/domainConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/domainConfigVersion.cmake"
            DESTINATION lib/cmake
            )

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/domainConfigVersion.cmake"
            VERSION "1.0"
            COMPATIBILITY AnyNewerVersion
    )

    export(EXPORT domainTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/domainTargets.cmake"
            NAMESPACE domain::)

    target_link_libraries(bsf PUBLIC
            domain)

else (!Qt5Widgets_FOUND)
# OOPS
message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

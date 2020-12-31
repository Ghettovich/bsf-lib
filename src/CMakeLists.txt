cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Needed for creating export
include(CMakePackageConfigHelpers)

# SET OPTION FOR SHARED LIBRARIES
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets DBus Core Sql Network Mqtt REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(bsf SHARED "")

    add_subdirectory(data)
    add_subdirectory(domain)
    add_subdirectory(parser)
    add_subdirectory(repo)
    add_subdirectory(mqtt)
    add_subdirectory(ui)

    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:include/bsf>"
            )

    install(TARGETS bsf
            EXPORT bsfTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    install(FILES bsf DESTINATION include)

    install(EXPORT bsfTargets
            FILE bsfTargets.cmake
            NAMESPACE bsf::
            DESTINATION lib/cmake
            )

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
            "${PROJECT_BINARY_DIR}/bsfConfig.cmake"
            INSTALL_DESTINATION lib/cmake
            )

    install(FILES
            "${PROJECT_BINARY_DIR}/bsfConfig.cmake"
            "${PROJECT_BINARY_DIR}/bsfConfigVersion.cmake"
            DESTINATION lib/cmake
            )

    export(EXPORT bsfTargets
            FILE "${PROJECT_BINARY_DIR}/bsfTargets.cmake"
            NAMESPACE bsf::
            )

    add_custom_command(
            TARGET bsf POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/data/bsf.db
            ${CMAKE_CURRENT_BINARY_DIR}/../apps/operator/app/bsf.db
    )

    add_custom_command(
            TARGET bsf POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/data/bsf.db
            ${CMAKE_CURRENT_BINARY_DIR}/../apps/scale/app/bsf.db
    )

    add_custom_command(
            TARGET bsf POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/../test/resource/database/bsf.db
            ${CMAKE_CURRENT_BINARY_DIR}/../test/resource/database/bsf.db
    )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

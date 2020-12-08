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

    # Set the property version pkconfig
    #set_property(TARGET repo PROPERTY VERSION 1.0)

    # Linkes files with QT
    target_link_libraries(bsf
            PUBLIC
            Qt5::Core
            Qt5::Sql)

    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )
#
#    install(TARGETS repo
#            EXPORT repoTargets
#            LIBRARY DESTINATION lib
#            ARCHIVE DESTINATION lib
#            RUNTIME DESTINATION bin
#            INCLUDES DESTINATION include
#            )
#
#    # install header file
#    install(FILES ${HEADER_FILES} DESTINATION include)
#
#    install(EXPORT repoTargets
#            FILE repoTargets.cmake
#            NAMESPACE repo::
#            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/repo
#            )
#
#    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#            "${CMAKE_CURRENT_BINARY_DIR}/repoConfig.cmake"
#            INSTALL_DESTINATION lib/cmake
#            )
#
#    install(FILES
#            "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/repoConfig.cmake"
#            "${PROJECT_BINARY_DIR}/repoConfigVersion.cmake"
#            DESTINATION lib/cmake
#            )
#
#    # generate the version file for the config file
#    write_basic_package_version_file(
#            "${CMAKE_CURRENT_BINARY_DIR}/repoConfigVersion.cmake"
#            VERSION "1.0"
#            COMPATIBILITY AnyNewerVersion
#    )
#
#    export(EXPORT repoTargets
#            FILE "${CMAKE_CURRENT_BINARY_DIR}/repoTargets.cmake"
#            NAMESPACE repo::
#            )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

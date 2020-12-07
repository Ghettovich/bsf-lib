cmake_minimum_required(VERSION 3.7...3.18)
project(repo)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/src/")

# find upstream packages
find_package(data)
find_package(domain)

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
    add_library(repo SHARED
            actionarduinorepo.cpp
            arduinorepo.cpp
            iodevicerepo.cpp
            logrepo.cpp
            reciperepo.cpp
            statecoderepo.cpp
            ${HEADER_LIST})

    # Linkes files with QT
    target_link_libraries(repo
            PRIVATE
            data::data
            domain::domain
            Qt5::Core
            Qt5::Sql)

    target_include_directories(repo
            PUBLIC

            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:include>")

    install(TARGETS repo
            EXPORT repoTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    # install header file
    install(FILES ${HEADER_FILES} DESTINATION include)

    install(EXPORT repoTargets
            FILE repoTargets.cmake
            NAMESPACE repo::
            DESTINATION lib/cmake
            )

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/repoConfig.cmake"
            INSTALL_DESTINATION lib/cmake
            )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/repoConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/repoConfig.cmake"
            DESTINATION lib/cmake)

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/repoConfigVersion.cmake"
            VERSION "1.0"
            COMPATIBILITY AnyNewerVersion
    )

    export(EXPORT repoTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/repoTargets.cmake"
            NAMESPACE repo::
            )

    target_link_libraries(bsf PUBLIC
            repo)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

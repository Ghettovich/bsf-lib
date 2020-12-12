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

    # Set the property version pkconfig
    #set_property(TARGET parser PROPERTY VERSION 1.0)

    # Linkes files with QT
    target_link_libraries(bsf
            PUBLIC
            Qt5::Core)

    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

#    install(TARGETS parser
#            EXPORT parserTargets
#            LIBRARY DESTINATION lib
#            ARCHIVE DESTINATION lib
#            RUNTIME DESTINATION bin
#            INCLUDES DESTINATION include
#            )
#
#    # install header file
#    install(FILES ${HEADER_FILES} DESTINATION include)
#
#    install(EXPORT parserTargets
#            FILE parserTargets.cmake
#            NAMESPACE parser::
#            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/parser
#            )
#
#    install(TARGETS parser DESTINATION lib)
#
#    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#            "${CMAKE_CURRENT_BINARY_DIR}/parserConfig.cmake"
#            INSTALL_DESTINATION lib/cmake
#            )
#
#    install(FILES
#            "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/parserConfig.cmake"
#            "${PROJECT_BINARY_DIR}/parserConfigVersion.cmake"
#            DESTINATION lib/cmake
#            )
#
#    # generate the version file for the config file
#    write_basic_package_version_file(
#            "${CMAKE_CURRENT_BINARY_DIR}/parserConfigVersion.cmake"
#            VERSION "1.0"
#            COMPATIBILITY AnyNewerVersion
#    )
#
#    export(EXPORT parserTargets
#            FILE "${CMAKE_CURRENT_BINARY_DIR}/parserTargets.cmake"
#            NAMESPACE parser::
#            )

else (!Qt5Widgets_FOUND)
# OOPS
message("could not find qt widgets")
endif (Qt5Widgets_FOUND)


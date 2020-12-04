cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        transformpayload.h)

# TARGET SOURCES
add_library(parser
        transformpayload.cpp
        ${HEADER_LIST})

# Set the property version pkconfig
set_property(TARGET parser PROPERTY VERSION 1.0)

# Linkes files with QT
target_link_libraries(parser PUBLIC
        domain
        Qt5::Core)

target_include_directories(parser
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>")

install(TARGETS parser
        EXPORT parserTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

# install header file
install(FILES ${HEADER_FILES} DESTINATION include)

install(EXPORT parserTargets
        FILE parserTargets.cmake
        NAMESPACE parser::
        DESTINATION lib/cmake
        )

install(TARGETS parser DESTINATION include)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/parserConfig.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/parserConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/parserConfigVersion.cmake"
        DESTINATION lib/cmake
        )

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/parserConfigVersion.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT parserTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/parserTargets.cmake")

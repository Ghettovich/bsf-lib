cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

# HEADER LIST
set(HEADER_LIST
        bsfdatabaseconfig.h)

# TARGET MAIN LIB
add_library(data SHARED
        bsfdatabaseconfig.cpp
        ${HEADER_LIST})

# Set the property version pkconfig
set_property(TARGET data PROPERTY VERSION 1.0)

# Linkes files with QT
target_link_libraries(data PUBLIC
        Qt5::Core
        Qt5::Sql)

# Define rules for exporting domain
target_include_directories(data
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>")

install(TARGETS data
        EXPORT dataTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

# install header file
install(FILES ${HEADER_FILES} DESTINATION include)

install(EXPORT dataTargets
        FILE dataTargets.cmake
        NAMESPACE data::
        DESTINATION lib/cmake
        )

install(TARGETS data DESTINATION lib)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/dataConfig.cmake"
        INSTALL_DESTINATION lib/cmake
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dataConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dataConfigVersion.cmake"
        DESTINATION lib/cmake
        )

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/dataConfigVersion.cmake"
        VERSION "1.0"
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT dataTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/dataTargets.cmake")

#target_link_libraries(bsflib PUBLIC
#        data)

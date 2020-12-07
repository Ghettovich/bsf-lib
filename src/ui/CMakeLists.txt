cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Needed for creating export
include(CMakePackageConfigHelpers)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/src/")

find_package(domain)
find_package(mqttclient
        PATHS "${CMAKE_BINARY_DIR}/src/mqtt")

#include_directories(${CMAKE_SOURCE_DIR}/lib)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            # WIDGETS
            widgets/beltfeeders/GroupBoxBeltFeeders.h
            widgets/binloaddrop/GroupBoxBinLoadDrop.h
            widgets/binrecipestatus/GroupBoxBinRecipeStatus.h
            widgets/devicestatus/TreeWidgetDeviceStatus.h
            widgets/liftupdown/GroupBoxLiftUpDown.h
            widgets/recipeconfig/GroupBoxRecipeConfig.h
            )

    add_library(ui
            # WIDGETS
            widgets/beltfeeders/GroupBoxBeltFeeders.cpp
            widgets/beltfeeders/groupboxbeltfeeders.ui
            widgets/binloaddrop/GroupBoxBinLoadDrop.cpp
            widgets/binloaddrop/groupboxbinloaddrop.ui
            widgets/binrecipestatus/GroupBoxBinRecipeStatus.cpp
            widgets/binrecipestatus/groupboxbinrecipestatus.ui
            widgets/devicestatus/TreeWidgetDeviceStatus.cpp
            widgets/devicestatus/treewidgetdevicestatus.ui
            widgets/liftupdown/GroupBoxLiftUpDown.cpp
            widgets/liftupdown/groupboxliftupdown.ui
            widgets/recipeconfig/GroupBoxRecipeConfig.cpp
            widgets/recipeconfig/groupboxrecipeconfig.ui
            )

    target_link_libraries(ui
            PRIVATE
            domain::domain
            mqttclient::mqttclient
            Qt5::Widgets)

    target_include_directories(ui
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:include>")

    install(TARGETS ui
            EXPORT uiTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include
            )

    # install header file
    install(FILES ${HEADER_FILES} DESTINATION include)

    install(EXPORT uiTargets
            FILE uiTargets.cmake
            NAMESPACE ui::
            DESTINATION lib/cmake
            )

    install(TARGETS ui DESTINATION lib)

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/uiConfig.cmake"
            INSTALL_DESTINATION lib/cmake
            )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/uiConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/uiConfigVersion.cmake"
            DESTINATION lib/cmake)

    # generate the version file for the config file
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/uiConfigVersion.cmake"
            VERSION "1.0"
            COMPATIBILITY AnyNewerVersion
    )

    export(EXPORT uiTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/uiTargets.cmake"
            NAMESPACE ui::)

    target_link_libraries(bsf PUBLIC
            ui)

else (!Qt5Widgets_FOUND)
# OOPS
message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

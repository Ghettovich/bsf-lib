cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Needed for creating export
include(CMakePackageConfigHelpers)

#list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/src/")

#find_package(domain 1.0 REQUIRED)
#find_package(mqtt 1.0 REQUIRED)

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

    target_sources(bsf PRIVATE
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
            # HEADER LIST
            PRIVATE
            ${HEADER_LIST}
            )

    # Set the property version pkconfig
    #set_property(TARGET ui PROPERTY VERSION 1.0)

    target_link_libraries(bsf
            PUBLIC
            Qt5::Widgets
            )

    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

#    install(TARGETS ui
#            EXPORT uiTargets
#            LIBRARY DESTINATION lib
#            ARCHIVE DESTINATION lib
#            RUNTIME DESTINATION bin
#            INCLUDES DESTINATION include
#            )
#
#    # install header file
#    install(FILES ${HEADER_FILES} DESTINATION include)
#
#    install(EXPORT uiTargets
#            FILE uiTargets.cmake
#            NAMESPACE ui::
#            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ui
#            )
#
#    install(TARGETS ui DESTINATION lib)
#
#    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#            "${CMAKE_CURRENT_BINARY_DIR}/uiConfig.cmake"
#            INSTALL_DESTINATION lib/cmake
#            )
#
#    install(FILES
#            "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/uiConfig.cmake"
#            "${PROJECT_BINARY_DIR}/uiConfigVersion.cmake"
#            DESTINATION lib/cmake)
#
#    # generate the version file for the config file
#    write_basic_package_version_file(
#            "${CMAKE_CURRENT_BINARY_DIR}/uiConfigVersion.cmake"
#            VERSION "1.0"
#            COMPATIBILITY AnyNewerVersion
#    )
#
#    export(EXPORT uiTargets
#            FILE "${CMAKE_CURRENT_BINARY_DIR}/uiTargets.cmake"
#            NAMESPACE ui::)

else (!Qt5Widgets_FOUND)
# OOPS
message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

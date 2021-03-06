cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Needed for creating export
include(CMakePackageConfigHelpers)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            # FONTS
            fonts/MaterialRegular.h
            fonts/QFontIcon.h
            # SCALE
            widgets/scale/Scale.h
            # INTERFACES
            widgets/interfaces/RecipeStatusInterface.h
            widgets/interfaces/IOWidgetStatusInterface.h
            # WIDGETS
            widgets/beltfeeders/GroupBoxBeltFeeders.h
            widgets/binloaddrop/GroupBoxBinLoadDrop.h
            widgets/binrecipestatus/GroupBoxBinRecipeStatus.h
            widgets/liftupdown/GroupBoxLiftUpDown.h
            widgets/recipeconfig/GroupBoxRecipeConfig.h
            widgets/statusproximities/ProximityTreeWidget.h
            widgets/statusrelays/RelayTreeWidget.h
            )

    target_sources(bsf PRIVATE
            # FONTS
            resource/theme.qrc
            fonts/MaterialRegular.cpp
            fonts/QFontIcon.cpp
            # INTERFACES
            widgets/interfaces/RecipeStatusInterface.cpp
            widgets/interfaces/IOWidgetStatusInterface.cpp
            # WIDGETS
            widgets/beltfeeders/GroupBoxBeltFeeders.cpp
            widgets/beltfeeders/groupboxbeltfeeders.ui
            widgets/binloaddrop/GroupBoxBinLoadDrop.cpp
            widgets/binloaddrop/groupboxbinloaddrop.ui
            widgets/binrecipestatus/GroupBoxBinRecipeStatus.cpp
            widgets/binrecipestatus/groupboxbinrecipestatus.ui
            widgets/liftupdown/GroupBoxLiftUpDown.cpp
            widgets/liftupdown/groupboxliftupdown.ui
            widgets/recipeconfig/GroupBoxRecipeConfig.cpp
            widgets/recipeconfig/groupboxrecipeconfig.ui
            widgets/statusproximities/ProximityTreeWidget.cpp
            widgets/statusproximities/proximitytreewidget.ui
            widgets/statusrelays/RelayTreeWidget.cpp
            widgets/statusrelays/relaytreewidget.ui
            # SCALE
            widgets/scale/Scale.cpp
            widgets/scale/scale.ui
            # HEADER LIST
            PRIVATE
            ${HEADER_LIST}
            )

    target_link_libraries(bsf
            PUBLIC
            Qt5::Core
            Qt5::Gui
            Qt5::Widgets
            )

    target_include_directories(bsf
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

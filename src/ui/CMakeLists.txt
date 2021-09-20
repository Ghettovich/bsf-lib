cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            # STACKED WIDGETS
            widgets/home/home.h
            widgets/recipe/RecipeWidget.h
            widgets/experimental/experimental.h
            )

    add_library(ui SHARED
            # STACKED WIDGETS
            widgets/home/home.cpp
            widgets/home/home.ui
            widgets/recipe/RecipeWidget.cpp
            widgets/recipe/recipewidget.ui
            widgets/experimental/experimental.cpp
            widgets/experimental/experimental.ui
            # HEADER LIST
            ${HEADER_LIST}
            )

    target_link_libraries(ui
            PUBLIC
            Qt5::Core
            Qt5::Widgets
            appservice
            domain)

    target_include_directories(ui
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

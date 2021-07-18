# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        appservice.broker/BrokerAppService.h
        appservice.prepare.recipe/PrepareRecipeAppService.h
        appservice.mix.recipe/MixRecipeAppService.h
        )

# ADD LIBRARY
add_library(appservice SHARED
        appservice.broker/BrokerAppService.cpp
        appservice.prepare.recipe/PrepareRecipeAppService.cpp
        appservice.mix.recipe/MixRecipeAppService.cpp
        # HEADERS
        ${HEADER_LIST})

# Linkes files with QT
target_link_libraries(appservice
        PUBLIC
        Qt5::Core
        domain
        service)

target_include_directories(appservice
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        )

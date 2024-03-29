# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core REQUIRED)

# HEADER LIST
set(HEADER_LIST
        appservice.broker/broker.appservice.h
        appservice.iodevices/iodevice.appservice.h
        appservice.prepare.recipe/preparerecipeappservice.h
        appservice.mix.recipe/mixrecipeappservice.h
        appservice.statemachine/statemachine.appservice.h
        appservice.statemachine/LiftTransition.h
        appservice.ui/ui.appservice.h
        )

# ADD LIBRARY
add_library(appservice SHARED
        appservice.broker/broker.appservice.cpp
        appservice.iodevices/iodevice.appservice.cpp
        appservice.prepare.recipe/preparerecipeappservice.cpp
        appservice.mix.recipe/mixrecipeappservice.cpp
        appservice.statemachine/statemachine.appservice.cpp
        appservice.ui/ui.appservice.cpp
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

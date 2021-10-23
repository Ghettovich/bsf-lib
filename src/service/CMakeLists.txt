# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Core Sql Mqtt Network REQUIRED)

# HEADER LIST
set(HEADER_LIST
        broker/BrokerService.h
        broker/client/MqttClient.h
        database/DatabaseService.h
        statemachine/machine.service.h
        ui/ui.service.h
        # INTERFACES
        ui/interfaces/sensor.widget.h
        # BUTTONS
        ui/button/relay.button.h
        # LABELS
        ui/label/proximity.label.h
        # LCD Number
        ui/scale/scale.lcdnumber.h
        # FONTS
        ui/fonts/MaterialRegular.h
        ui/fonts/QFontIcon.h
        statemachine/machine.service.cpp statemachine/machine.service.h)

# ADD LIBRARY
add_library(service SHARED
        broker/BrokerService.cpp
        broker/client/MqttClient.cpp
        database/DatabaseService.cpp
        statemachine/machine.service.cpp
        ui/ui.service.cpp
        # INTERFACES
        ui/interfaces/sensor.widget.cpp
        # BUTTONS
        ui/button/relay.button.cpp
        # LABELS
        ui/label/proximity.label.cpp
        # LCD Number
        ui/scale/scale.lcdnumber.cpp
        # FONTS
        ui/resource/theme.qrc
        ui/fonts/MaterialRegular.cpp
        ui/fonts/QFontIcon.cpp
        # HEADER LIST
        ${HEADER_LIST})

# Linkes files with QT
target_link_libraries(service
        PUBLIC
        Qt5::Core
        Qt5::Sql
        Qt5::Mqtt
        Qt5::Network
        Qt5::Widgets
        )

target_include_directories(service
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        )

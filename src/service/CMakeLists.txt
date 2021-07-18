# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql Mqtt Network REQUIRED)

# HEADER LIST
set(HEADER_LIST
        broker/BrokerService.h
        broker/client/MqttClient.h
        database/DatabaseService.h
        )

# ADD LIBRARY
add_library(service SHARED
        broker/BrokerService.cpp
        broker/client/MqttClient.cpp
        database/DatabaseService.cpp
        # HEADER LIST
        ${HEADER_LIST})

# Linkes files with QT
target_link_libraries(service
        PUBLIC
        Qt5::Core
        Qt5::Sql
        Qt5::Mqtt
        Qt5::Network
        )

target_include_directories(service
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        )

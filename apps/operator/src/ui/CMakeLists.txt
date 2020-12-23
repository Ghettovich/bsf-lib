cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Network Widgets REQUIRED)

if (Qt5Widgets_FOUND)

    set(HEADER_LIST
            # MAIN
            main/MainWindow.h
            # MQTT
            mqttclient/OperatorMqttClient.h
            mqttsubscription/SubscriptionWindow.h
            )

    target_sources(bsfOperator
            PRIVATE
            # MAIN
            main/MainWindow.cpp
            main/mainwindow.ui
            # MQTT
            mqttclient/OperatorMqttClient.cpp
            mqttclient/operatormqttclient.ui
            mqttsubscription/SubscriptionWindow.cpp
            mqttsubscription/subscriptionwindow.ui
            PUBLIC
            ${HEADER_LIST})

    target_link_libraries(bsfOperator PUBLIC
            Qt5::Network
            Qt5::Widgets)

    target_include_directories(bsfOperator
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")


else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
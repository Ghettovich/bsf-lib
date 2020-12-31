cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core Mqtt REQUIRED)

enable_testing()

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            tst_mqtt.h)

    # TARGET SOURCES
#    target_sources(srcTestLib
#            PRIVATE
#            tst_mqtt.cpp
#            PUBLIC
#            ${HEADER_LIST})
    add_executable(MqttClientTest
            tst_mqtt.cpp
            ${HEADER_LIST}
            ${CMAKE_CURRENT_SOURCE_DIR}/../resource/jsonPayload.qrc
            )


    target_link_libraries(MqttClientTest PRIVATE
            bsf
            Qt5::Test
            Qt5::Mqtt
            Qt5::Core
            )

    target_include_directories(MqttClientTest PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    add_test(mqttClientTest MqttClientTest)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            tst_transformpayload.h)

    # ADD TEST EXECUTABLE
    add_executable(TransformPayloadTest
            tst_transformpayload.cpp
            tst_transformpayload.h
            ${CMAKE_CURRENT_SOURCE_DIR}/../resource/jsonPayload.qrc
            )

    target_link_libraries(TransformPayloadTest PRIVATE
            bsf
            Qt5::Test
            Qt5::Core)

    target_include_directories(TransformPayloadTest PRIVATE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

    add_test(transformPayloadTest TransformPayloadTest)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)


include(CodeCoverage)

set(COVERAGE_EXCLUDES "dir1/*")
set(setup_target_for_coverage_gcovr_html
   NAME DomainCoverage
   EXECUTABLE DomainTest
   BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src"
   EXCLUDE "dir2/*")

setup_target_for_coverage_gcovr_xml(${setup_target_for_coverage_gcovr_html})

enable_testing()

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            tst_Recipe.h
            tst_Arduino.h
            )

    # ADD TEST EXECUTABLE
    add_executable(DomainTest
            autotest.cpp
            tst_Recipe.cpp
            tst_Arduino.cpp
            ${HEADER_LIST}
            ${CMAKE_CURRENT_SOURCE_DIR}/../resource/jsonPayload.qrc
            )

    target_link_libraries(DomainTest PRIVATE
            bsf
            Qt5::Test
            Qt5::Core
            )

    target_include_directories(DomainTest PRIVATE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    #add_test(domaintest DomainTest)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
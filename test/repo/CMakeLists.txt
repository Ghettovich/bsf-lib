cmake_minimum_required(VERSION 3.7...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5Test REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

enable_testing()

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            tst_actionarduinorepo.h
            tst_arduinorepo.h
            tst_iodevicerepo.h
            tst_logrepo.h
            tst_reciperepo.h
            tst_statecoderepo.h)

    # ADD TEST EXECUTABLE
    add_executable(RepositoryTest
            autotest.cpp
            tst_actionarduinorepo.cpp
            tst_arduinorepo.cpp
            tst_iodevicerepo.cpp
            tst_logrepo.cpp
            tst_reciperepo.cpp
            tst_statecoderepo.cpp
            ${HEADER_LIST})

    target_link_libraries(RepositoryTest PRIVATE
            bsf
            Qt5::Test
            Qt5::Core)

    target_include_directories(RepositoryTest PRIVATE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

    add_test(repositoryTest RepositoryTest)

    add_custom_command(
            TARGET RepositoryTest POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/bsf.db
            ${CMAKE_CURRENT_BINARY_DIR}/bsf.db
    )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
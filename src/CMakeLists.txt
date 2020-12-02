cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET OPTION FOR SHARED LIBRARIES
#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets DBus Core Sql Network Mqtt REQUIRED)

if (Qt5Widgets_FOUND)

    add_subdirectory(data)
    add_subdirectory(domain)
    add_subdirectory(mqtt)
    add_subdirectory(repo)
    add_subdirectory(ui)

    #install(EXPORT bsflibTargets DESTINATION lib)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

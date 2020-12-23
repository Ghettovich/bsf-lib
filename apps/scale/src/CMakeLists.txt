cmake_minimum_required(VERSION 3.13...3.18)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#list(APPEND CMAKE_PREFIX PATH "${PROJECT_BINARY_DIR}/../../")

#find_package(bsf REQUIRED
#        PATHS "${PROJECT_BINARY_DIR}/../../")

# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Widgets Sql Network REQUIRED)

if (Qt5Widgets_FOUND)

    add_library(bsfWeightstationlib SHARED "")

    # ADD SOURCES TO BSF-WEIGHTSTATION LIB
    add_subdirectory(ui)

    target_link_libraries(bsfWeightstationlib PUBLIC
            bsf
            )

    install(TARGETS bsfWeightstationlib DESTINATION include)

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)
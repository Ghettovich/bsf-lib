# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            action.h
            arduino.h
            bafalog.h
            statecode.h
            component/component.h
            component/componentrepo.h
            recipe/recipe.h
            recipe/reciperepo.h
            recipe/recipeservice.h
            recipe.selection/recipeselection.h
            recipe.selection/recipeselectionservice.h
            iodevice/iodevice.h
            iodevice/detectionsensor.h
            iodevice/relay.h
            iodevice/weightcensor.h
            iodevice/iodevicetype.h
            iodevice/iodeviceservice.h
            iodevice/iodevicerepo.h
            )

    # TARGET SOURCES
    add_library(domain SHARED
            action.cpp
            arduino.cpp
            bafalog.cpp
            statecode.cpp
            component/component.cpp
            component/componentrepo.cpp
            recipe/recipe.cpp
            recipe/reciperepo.cpp
            recipe/recipeservice.cpp
            recipe.selection/recipeselection.cpp
            recipe.selection/recipeselectionservice.cpp
            iodevice/iodevice.cpp
            iodevice/detectionsensor.cpp
            iodevice/relay.cpp
            iodevice/weightcensor.cpp
            iodevice/iodevicetype.cpp
            iodevice/iodeviceservice.cpp
            iodevice/iodevicerepo.cpp
            # HEADER LIST
            ${HEADER_LIST}
            )

    # Link files with QT
    target_link_libraries(domain
            PUBLIC
            Qt5::Core
            Qt5::Sql
            service
            )

    # Define rules for exporting domain
    target_include_directories(domain
            PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

else (!Qt5Widgets_FOUND)
    # OOPS
    message("could not find qt widgets")
endif (Qt5Widgets_FOUND)

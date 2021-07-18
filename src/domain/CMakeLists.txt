# find Qt5 and required components | Qt5_DIR
find_package(Qt5 COMPONENTS Core Sql REQUIRED)

if (Qt5Widgets_FOUND)

    # HEADER LIST
    set(HEADER_LIST
            action.h
            arduino.h
            bafalog.h
            component/component.h
            component/componentrepo.h
            detectionsensor.h
            iodevice.h
            iodevicetype.h
            recipe/recipe.h
            recipe/reciperepo.h
            relay.h
            statecode.h
            weightcensor.h
            iodevice/iodeviceservice.h
            iodevice/iodevicerepo.h
            )

    # TARGET SOURCES
    add_library(domain SHARED
            action.cpp
            arduino.cpp
            bafalog.cpp
            component/component.cpp
            component/componentrepo.cpp
            detectionsensor.cpp
            iodevice.cpp
            iodevicetype.cpp
            recipe/recipe.cpp
            recipe/reciperepo.cpp
            relay.cpp
            statecode.cpp
            weightcensor.cpp
            iodevice/iodeviceservice.cpp
            iodevice/iodevicerepo.cpp
            # WIDGET ENUM
            BsfWidgetEnum.h
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

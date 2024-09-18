cmake_minimum_required(VERSION 3.16)

project(Canprocess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the necessary Qt5 components
find_package(Qt5 5.15 REQUIRED COMPONENTS Quick DBus SerialBus)

# Setup the project with standard Qt5 configurations
# (Qt5 doesn't have qt_standard_project_setup, so skip or use manual setup)
# qt_standard_project_setup(REQUIRES 5.15)

# Define the executable for the project
qt5_add_executable(appCanprocess
    main.cpp
)

# Define the QML module and resources
qt5_add_qml_module(appCanprocess
    URI Canprocess
    VERSION 1.0
    QML_FILES
        Main.qml
        Cluster.qml 
    RESOURCES resources.qrc
    SOURCES
        battery.h battery.cpp
        canreceiver.h canreceiver.cpp
        speedcontrol.h speedcontrol.cpp
)

qt5_add_resources(appCanprocess "resources"
    PREFIX "/"
    FILES
        Main.qml
        Cluster.qml
        framefffinal.png
        needle.png
        needle_battery.png
)

# Set target properties for macOS/iOS (optional, can be customized or removed)
set_target_properties(appCanprocess PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# Link the necessary Qt5 libraries
target_link_libraries(appCanprocess
    PRIVATE Qt5::Quick Qt5::DBus Qt5::SerialBus
)

# Install instructions
include(GNUInstallDirs)
install(TARGETS appCanprocess
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

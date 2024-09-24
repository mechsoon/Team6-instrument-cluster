cmake_minimum_required(VERSION 3.16)

project(Canprocess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick DBus)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appCanprocess
    src/main.cpp
)

qt_add_qml_module(appCanprocess
    URI Canprocess
    VERSION 1.0
    QML_FILES
        src/Main.qml
        SOURCES 
        src/SpeedController.h src/SpeedContoller+EMA.cpp
        QML_FILES 
        src/Cluster.qml 
        RESOURCES 
        src/resources.qrc
        RESOURCES
        SOURCES 
        src/battery.h src/battery.cpp

)
qt_add_resources(appCanprocess "resources"
    PREFIX "/"
    FILES
        src/Main.qml
        src/Cluster.qml
        src/framefffinal.png
        src/needle.png
        src/needle_battery.png
        src/low_battery.png

        
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCanprocess PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCanprocess
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCanprocess
    PRIVATE Qt6::Quick Qt6::DBus
)




include(GNUInstallDirs)
install(TARGETS appCanprocess
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

cmake_minimum_required(VERSION 3.16)

project(ThreeThings VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Widgets Sql REQUIRED)

qt_add_executable(appThreeThings
    main.cpp
    filtermodel.h
    filtermodel.cpp
    sqlmodel.h
    sqlmodel.cpp
    dbhelper.h
    dbhelper.cpp
)

qt_add_qml_module(appThreeThings
    URI ThreeThings
    VERSION 1.0
    QML_FILES main.qml TodoItem.qml CustomButton.qml
)

set_target_properties(appThreeThings PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appThreeThings
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appThreeThings
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::Sql)

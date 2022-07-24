cmake_minimum_required(VERSION 3.22.2)

project(QLink VERSION 1.0
    DESCRIPTION "Link-Link written in QT"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)



find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(extern)
add_subdirectory(tests)


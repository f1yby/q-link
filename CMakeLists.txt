cmake_minimum_required(VERSION 3.18.4)

project(QLink VERSION 1.0
    DESCRIPTION "Link-Link written in QT"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)


include(FetchContent)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)
qt_standard_project_setup()


FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
 spdlog
 GIT_REPOSITORY https://github.com/gabime/spdlog.git
 GIT_TAG v1.x
)

FetchContent_GetProperties(spdlog)
if (NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)


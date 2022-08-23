add_executable(QLINK_APP qlink.cpp)

target_link_libraries(QLINK_APP PRIVATE spdlog::spdlog)
target_link_libraries(QLINK_APP PRIVATE MainWindow Qt6::Widgets)
target_include_directories(QLINK_APP PRIVATE ../include)
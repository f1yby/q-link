add_executable(QLINK_APP qlink.cpp)

target_link_libraries(QLINK_APP MainWindow Menu  spdlog::spdlog Qt6::Widgets)
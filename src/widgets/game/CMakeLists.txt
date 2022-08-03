add_widget_library(Game game)
target_link_libraries(Game PRIVATE Qt6::Widgets)
target_include_directories(Game PRIVATE "${LIB_INCLUDE_DIR}/link_link")
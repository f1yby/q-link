add_library(LinkLink link_link.cpp block/type.cpp block/diamond.cpp block/player.cpp block/blank.cpp )
target_include_directories(LinkLink PRIVATE "${LIB_INCLUDE_DIR}/link_link")
target_link_libraries(LinkLink PRIVATE Qt6::Gui)
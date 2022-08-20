add_library(LinkLink "link_link.cpp" "block/type.cpp" "block/diamond.cpp" "block/player.cpp" "block/blank.cpp" "block/wall.cpp" "block/path.cpp" "block/special.cpp")
target_include_directories(LinkLink PUBLIC "${LIB_INCLUDE_DIR}/link_link" "${LIB_INCLUDE_DIR}/link_link/block")
target_link_libraries(LinkLink PRIVATE Qt6::Gui)
add_library(LinkLink
        OBJECT
        "link_link.cpp"
        "block/type.cpp"
        "block/diamond.cpp"
        "block/player.cpp"
        "block/blank.cpp"
        "block/wall.cpp"
        "block/path.cpp"
        "block/special.cpp")
target_link_libraries(LinkLink PRIVATE Qt6::Gui spdlog::spdlog)
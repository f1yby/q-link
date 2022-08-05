#set(HEADER_LIST
#        "${LIB_INCLUDE_DIR}/link_link/link_link.h"
#        "${LIB_INCLUDE_DIR}/link_link/operation.h"
#        "${LIB_INCLUDE_DIR}/link_link/reaction.h"
#        "${LIB_INCLUDE_DIR}/link_link/block/block_interface.h"
#        "${LIB_INCLUDE_DIR}/link_link/block/diamond.h"
#        "${LIB_INCLUDE_DIR}/link_link/block/blank.h"
#        "${LIB_INCLUDE_DIR}/link_link/block/player.h"
#        "${LIB_INCLUDE_DIR}/link_link/block/type.h"
#        "${LIB_INCLUDE_DIR}/link_link/block/wall.h"
#
#        )

add_library(LinkLink link_link.cpp block/type.cpp block/diamond.cpp block/player.cpp block/blank.cpp block/wall.cpp)
target_include_directories(LinkLink PUBLIC "${LIB_INCLUDE_DIR}/link_link" "${LIB_INCLUDE_DIR}/link_link/block")
target_link_libraries(LinkLink PRIVATE Qt6::Gui)
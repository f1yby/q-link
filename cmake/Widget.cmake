function(ADD_WIDGET_LIBRARY WIDGET_CLASS_NAME WIDGET_FILE_NAME)
    add_library("${WIDGET_CLASS_NAME}" STATIC "${WIDGET_FILE_NAME}.cpp" "${WIDGET_FILE_NAME}.ui" "../../include/widget/${WIDGET_FILE_NAME}.h")
endfunction(ADD_WIDGET_LIBRARY)

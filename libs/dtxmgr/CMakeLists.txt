file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(dtxmgr STATIC ${SRC})
target_include_directories(dtxmgr PUBLIC . PRIVATE ../../engine/runtime/shared ../../engine/runtime/kernel/mem ../../engine/runtime/kernel/src) # kernel inclusions breaks...
target_link_libraries(dtxmgr PUBLIC ltsdk stdlith lttools)
set_target_properties(dtxmgr PROPERTIES FOLDER libs)
target_precompile_headers(dtxmgr PRIVATE stdafx.h)

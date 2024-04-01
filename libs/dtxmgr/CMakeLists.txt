file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(dtxmgr STATIC ${SRC})
target_include_directories(dtxmgr PUBLIC .)
target_link_libraries(dtxmgr PUBLIC ltsdk stdlith ltmem squish)
set_target_properties(dtxmgr PROPERTIES FOLDER libs)

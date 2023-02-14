file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(ButeMgr STATIC ${SRC})
target_include_directories(ButeMgr PUBLIC .)
target_link_libraries(ButeMgr PUBLIC ltsdk)
set_target_properties(ButeMgr PROPERTIES FOLDER libs)
target_precompile_headers(ButeMgr PRIVATE stdafx.h)

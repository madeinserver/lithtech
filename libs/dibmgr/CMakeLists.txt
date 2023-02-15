file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(dibmgr STATIC ${SRC})
target_include_directories(dibmgr PUBLIC .)
target_link_libraries(dibmgr PUBLIC ltsdk)
set_target_properties(dibmgr PROPERTIES FOLDER libs)
target_precompile_headers(dibmgr PRIVATE stdafx.h)

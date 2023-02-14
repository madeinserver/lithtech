file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(RegMgr32 STATIC ${SRC})
target_include_directories(RegMgr32 PUBLIC .)
target_link_libraries(RegMgr32 PUBLIC ltsdk)
set_target_properties(RegMgr32 PROPERTIES FOLDER libs)
target_precompile_headers(RegMgr32 PRIVATE STDAFX.H)

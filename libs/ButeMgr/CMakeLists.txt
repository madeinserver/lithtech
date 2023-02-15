file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(ButeMgr STATIC ${SRC})
target_include_directories(ButeMgr PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ButeMgr PUBLIC ltsdk CryptMgr stdlith rezmgr lith)
set_target_properties(ButeMgr PROPERTIES FOLDER libs)
target_precompile_headers(ButeMgr PRIVATE stdafx.h)
target_compile_definitions(ButeMgr PUBLIC -D_USE_REZFILE_)

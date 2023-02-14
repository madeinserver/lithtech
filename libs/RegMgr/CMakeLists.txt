file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(RegMgr STATIC ${SRC})
target_include_directories(RegMgr PUBLIC .)
target_link_libraries(RegMgr PUBLIC ltsdk)
set_target_properties(RegMgr PROPERTIES FOLDER libs)

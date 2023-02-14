file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(rezmgr STATIC ${SRC})
target_include_directories(rezmgr PUBLIC .)
target_link_libraries(rezmgr PUBLIC ltsdk lith)
set_target_properties(rezmgr PROPERTIES FOLDER libs)

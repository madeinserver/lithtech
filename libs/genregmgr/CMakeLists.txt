file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(genregmgr STATIC ${SRC})
target_include_directories(genregmgr PUBLIC .)
target_link_libraries(genregmgr PUBLIC ltsdk)
set_target_properties(genregmgr PROPERTIES FOLDER libs)

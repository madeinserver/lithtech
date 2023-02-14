file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(ltamgr STATIC ${SRC})
target_include_directories(ltamgr PUBLIC .)
target_link_libraries(ltamgr PUBLIC ltsdk)
set_target_properties(ltamgr PROPERTIES FOLDER libs)

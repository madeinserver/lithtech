file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(lith STATIC ${SRC})
target_include_directories(lith PUBLIC .)
target_link_libraries(lith PUBLIC ltsdk)
set_target_properties(lith PROPERTIES FOLDER libs)

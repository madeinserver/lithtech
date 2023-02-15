file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(aegis STATIC ${SRC})
target_include_directories(aegis PUBLIC .)
target_link_libraries(aegis PUBLIC ltsdk)
set_target_properties(aegis PROPERTIES FOLDER libs)

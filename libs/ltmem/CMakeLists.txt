file(GLOB SRC "*.cpp" "*.h")
source_group("" FILES ${SRC})

add_library(ltmem STATIC ${SRC})
target_include_directories(ltmem PUBLIC .)
target_link_libraries(ltmem PUBLIC stdlith)
set_target_properties(ltmem PROPERTIES FOLDER libs)
target_precompile_headers(ltmem PRIVATE stdafx.h)

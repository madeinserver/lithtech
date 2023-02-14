file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(StackTracer STATIC ${SRC})
target_include_directories(StackTracer PUBLIC .)
target_link_libraries(StackTracer PUBLIC ltsdk)
set_target_properties(StackTracer PROPERTIES FOLDER libs)
target_precompile_headers(StackTracer PRIVATE stdafx.h)

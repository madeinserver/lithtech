file(GLOB SRC "*.h" "*.cpp" "*.rc")
source_group("" FILES ${SRC})
add_executable(DtxOptimizer ${SRC})
set_target_properties(DtxOptimizer PROPERTIES FOLDER "tools")
target_link_libraries(DtxOptimizer PRIVATE ltsdk stdlith lttools)
target_precompile_headers(DtxOptimizer PRIVATE stdafx.h)

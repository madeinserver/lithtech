file(GLOB SRC "*.h" "*.cpp" "*.rc" "*.def")
source_group("" FILES ${SRC})
add_library(DtxShellEx SHARED ${SRC})
set_target_properties(DtxShellEx PROPERTIES FOLDER "tools")
target_link_libraries(DtxShellEx PRIVATE ltsdk stdlith lttools)
target_precompile_headers(DtxShellEx PRIVATE stdafx.h)

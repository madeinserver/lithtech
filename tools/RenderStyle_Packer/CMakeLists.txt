file(GLOB SRC "*.h" "*.cpp" "*.rc")
source_group("" FILES ${SRC})
add_executable(RenderStylePacker WIN32 ${SRC})
set_target_properties(RenderStylePacker PROPERTIES FOLDER "tools")
target_link_libraries(RenderStylePacker PRIVATE ltsdk stdlith lttools Winmm)
target_precompile_headers(RenderStylePacker PRIVATE StdAfx.h)
target_include_directories(RenderStylePacker PRIVATE ${DirectX_D3DX9_INCLUDE_DIR})

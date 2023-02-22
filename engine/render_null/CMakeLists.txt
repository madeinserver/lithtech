file(GLOB SRC "*.h" "*.cpp" "*.rc")
source_group("" FILES ${SRC})

add_library(RenderNull SHARED ${SRC})
target_include_directories(RenderNull PRIVATE .)
target_link_libraries(RenderNull PRIVATE ltsdk ltmem)
set_target_properties(RenderNull PROPERTIES FOLDER engine/render)
out_name(RenderNull RenderDrv)

file(GLOB SRC "*.h" "*.cpp" "*.rc")
source_group("" FILES ${SRC})
add_executable(WinLTC WIN32 ${SRC})
set_target_properties(WinLTC PROPERTIES FOLDER "tools")
target_link_libraries(WinLTC PRIVATE ltsdk stdlith lttools)

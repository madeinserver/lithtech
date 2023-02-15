file(GLOB SRC "*.h" "*.cpp" "*.rc")

add_executable(WinLTC WIN32 ${SRC})

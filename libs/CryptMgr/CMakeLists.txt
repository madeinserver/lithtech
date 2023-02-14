file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(CryptMgr STATIC ${SRC})
target_include_directories(CryptMgr PUBLIC .)
target_link_libraries(CryptMgr PUBLIC ltsdk)
set_target_properties(CryptMgr PROPERTIES FOLDER libs)

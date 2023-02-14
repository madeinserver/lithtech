file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(stdlith STATIC ${SRC})
target_include_directories(stdlith PUBLIC .)
target_link_libraries(stdlith PUBLIC ZLIB::ZLIB ltsdk)
set_target_properties(stdlith PROPERTIES FOLDER libs)
target_precompile_headers(stdlith PRIVATE stdafx.h)

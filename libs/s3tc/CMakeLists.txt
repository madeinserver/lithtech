file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(s3tc STATIC ${SRC})
target_include_directories(s3tc PUBLIC .)
set_target_properties(s3tc PROPERTIES FOLDER libs)

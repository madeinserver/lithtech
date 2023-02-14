set(SRC Init.cpp resource.h ltmsg.rc)
add_library(ltmsg SHARED ${SRC})
source_group("" FILES ${SRC})
set_target_properties(ltmsg PROPERTIES FOLDER engine)

file(GLOB SRC "*.h" "*.cpp" "*.rc")
source_group("" FILES ${SRC})

add_library(SoundNull SHARED ${SRC})
target_include_directories(SoundNull PRIVATE .)
target_link_libraries(SoundNull PRIVATE ltsdk ltmem)
set_target_properties(SoundNull PROPERTIES FOLDER engine/sound)
target_precompile_headers(SoundNull PRIVATE StdAfx.h)
out_name(SoundNull SndDrv)

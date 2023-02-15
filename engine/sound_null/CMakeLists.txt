file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(SoundNull SHARED ${SRC})
target_include_directories(SoundNull PRIVATE .)
target_link_libraries(SoundNull PRIVATE ltsdk ltmem)
set_target_properties(SoundNull PROPERTIES FOLDER engine/sound)
target_precompile_headers(SoundNull PRIVATE StdAfx.h)
set_target_properties(SoundNull PROPERTIES OUTPUT_NAME SndDrv OUTPUT_NAME_DEBUG SndDrv OUTPUT_NAME_RELEASE SndDrv OUTPUT_NAME_MINSIZEREL SndDrv OUTPUT_NAME_RELWITHDEBINFO SndDrv)

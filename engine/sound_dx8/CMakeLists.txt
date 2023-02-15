file(GLOB SRC "*.h" "*.cpp")
source_group("" FILES ${SRC})

add_library(SoundDx8 SHARED ${SRC})
target_include_directories(SoundDx8 PRIVATE .)
target_link_libraries(SoundDx8 PRIVATE ltsdk ltmem dsound dxguid Winmm Msacm32)
target_link_directories(SoundDx8 PRIVATE ${DirectX_ROOT_DIR}/Lib/${DX_ARCH})
set_target_properties(SoundDx8 PROPERTIES FOLDER engine/sound)
target_precompile_headers(SoundDx8 PRIVATE StdAfx.h)
set_target_properties(SoundDx8 PROPERTIES OUTPUT_NAME SndDrv OUTPUT_NAME_DEBUG SndDrv OUTPUT_NAME_RELEASE SndDrv OUTPUT_NAME_MINSIZEREL SndDrv OUTPUT_NAME_RELWITHDEBINFO SndDrv)


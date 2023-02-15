runtime_src(controlfilemgr SERVER)
runtime_src(info SERVER)
runtime_src(lithtemplate SERVER)
runtime_src(model SERVER)
runtime_src(physics SERVER)
runtime_src(server SERVER)
runtime_src(world SERVER)
runtime_src(shared SERVER)
runtime_src(client SERVER)
runtime_src(sound SERVER)

kernel_src(io SERVER)
kernel_src(mem SERVER)
kernel_src(net SERVER)
kernel_src(src SERVER)

list(REMOVE_ITEM LT_SERVER_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusic_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusic_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusiccontrolfile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusiccontrolfile.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusicloader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusicloader.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/win/binkvideomgrimpl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/win/binkvideomgrimpl.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/render.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/render.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltrendermgr_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltrendermgr_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/input.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/input.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/text_mgr.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/text_mgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/interface_helpers.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/interface_helpers.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/musicdriver.h
    ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/musicdriver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/sys/win/winclientde_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/sys/win/winclientde_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/client/sys/win/winconsole_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/client/sys/win/winconsole_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/sys/win/texturestringimage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/sys/win/customfontfilemgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/consolecommands.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/consolecommands.h
    ${CMAKE_CURRENT_LIST_DIR}/client/texturestringimage.h
    ${CMAKE_CURRENT_LIST_DIR}/client/customfontfilemgr.h
    ${CMAKE_CURRENT_LIST_DIR}/client/shellnet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/texturestring.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/texturestring.h
    ${CMAKE_CURRENT_LIST_DIR}/client/clientmgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/clientmgr.h
    ${CMAKE_CURRENT_LIST_DIR}/client/clientshell.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/clientshell.h
    ${CMAKE_CURRENT_LIST_DIR}/client/shelltransfer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_iltphysics.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_iltmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_ilcommon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_iltvideomgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_filemgr.h
    ${CMAKE_CURRENT_LIST_DIR}/client/client_filemgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/lttexturestring.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/lttexturestring.h
    ${CMAKE_CURRENT_LIST_DIR}/client/client_ticks.h
    ${CMAKE_CURRENT_LIST_DIR}/client/client_ticks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_formatmgr.h
    ${CMAKE_CURRENT_LIST_DIR}/client/client_formatmgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_graphmgr.h
    ${CMAKE_CURRENT_LIST_DIR}/client/client_graphmgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_loaderthread.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/client_loaderthread.h
    ${CMAKE_CURRENT_LIST_DIR}/client/setupobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/setupobject.h
    ${CMAKE_CURRENT_LIST_DIR}/client/consolecommands.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/consolecommands.h
    ${CMAKE_CURRENT_LIST_DIR}/client/clientde_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/clientde_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/client/errorlog.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/errorlog.h
    ${CMAKE_CURRENT_LIST_DIR}/client/cnet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/particlesystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/particlesystem.h
    ${CMAKE_CURRENT_LIST_DIR}/client/volumeeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/volumeeffect.h
    ${CMAKE_CURRENT_LIST_DIR}/client/world_client_bsp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/ltinfo_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/ltinfo_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/client/ltbenchmark_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/client/ltbenchmark_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/console.h
    ${CMAKE_CURRENT_LIST_DIR}/client/console.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/predict.h
    ${CMAKE_CURRENT_LIST_DIR}/client/predict.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/shellutil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/sprite.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/sprite.h
    ${CMAKE_CURRENT_LIST_DIR}/client/client_iltcommon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/cmoveabstract.h
    ${CMAKE_CURRENT_LIST_DIR}/client/cmoveabstract.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/ltmessage_client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/ltmessage_client.h
    ${CMAKE_CURRENT_LIST_DIR}/client/memorywatch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/client/memorywatch.h
    ${CMAKE_CURRENT_LIST_DIR}/client/cutil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/world/world_client_bsp.h
    ${CMAKE_CURRENT_LIST_DIR}/shared/dtxmgr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/shared/findobj.cpp
    ${CMAKE_CURRENT_LIST_DIR}/shared/findobj.h
    ${CMAKE_CURRENT_LIST_DIR}/shared/debuggeometry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/shared/debuggeometry.h
    ${CMAKE_CURRENT_LIST_DIR}/sound/soundinstance.h
    ${CMAKE_CURRENT_LIST_DIR}/sound/soundinstance.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sound/soundbuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/sound/soundbuffer.cpp    
    ${CMAKE_CURRENT_LIST_DIR}/sound/soundmgr.h
    ${CMAKE_CURRENT_LIST_DIR}/sound/soundmgr.cpp
)

list(APPEND LT_SERVER_DEFINE -DSTDLITH_ALLOC_OVERRIDE -DDE_SERVER_COMPILE)

if (WIN32)
    set(LT_SERVER_RESOURCES
        server/sys/win/server.def
        server/sys/win/server.rc
        server/sys/win/resource.h
    )

    source_group("resources" FILES ${LT_SERVER_RESOURCES})
endif()

add_library(server SHARED ${LT_SERVER_SOURCE} ${LT_SERVER_RESOURCES})
runtime_link(server SERVER)
runtime_link(server SHARED)
set_target_properties(server PROPERTIES FOLDER engine)
target_precompile_headers(server PRIVATE shared/bdefs.h)

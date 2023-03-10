runtime_src(controlfilemgr CLIENT)
runtime_src(info CLIENT)
runtime_src(lithtemplate CLIENT)
runtime_src(model CLIENT)
runtime_src(physics CLIENT)
runtime_src(client CLIENT)
runtime_src(server CLIENT)
runtime_src(sound CLIENT)
runtime_src(ui CLIENT)
runtime_src(world CLIENT)
runtime_src(shared CLIENT)

kernel_src(io CLIENT)
kernel_src(mem CLIENT)
kernel_src(net CLIENT)
kernel_src(src CLIENT)

if (NOT USE_DIRECTMUSIC)
    list(REMOVE_ITEM LT_CLIENT_SOURCE
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusic_impl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusic_impl.h
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusiccontrolfile.cpp
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusiccontrolfile.h
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusicloader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/sys/win/ltdirectmusicloader.h
    )
else()
    list(APPEND LT_CLIENT_DEFINE -DUSE_DIRECTMUSIC)
endif()

if (NOT USE_BINKVIDEO)
    list(REMOVE_ITEM LT_CLIENT_SOURCE
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/win/binkvideomgrimpl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/kernel/src/win/binkvideomgrimpl.h
    )
else()
    list(APPEND LT_CLIENT_DEFINE -DIHAVEPURCHASEDBINK)
endif()

list(APPEND LT_CLIENT_LIBS Freetype::Freetype)
list(APPEND LT_CLIENT_DEFINE -DDE_LOCAL_SERVERBIND -DDE_CLIENT_COMPILE)

if (WIN32)
    set(LT_CLIENT_RESOURCES 
        client/sys/win/idr_main.ico
        client/sys/win/lithtech.rc
        client/sys/win/resource.h
    )
    list(APPEND LT_CLIENT_LIBS dinput8 dxguid)
    source_group("resources" FILES ${LT_CLIENT_RESOURCES})
endif()

add_executable(lithtech WIN32 ${LT_CLIENT_SOURCE} ${LT_CLIENT_RESOURCES})
runtime_link(lithtech CLIENT)
runtime_link(lithtech SHARED)
set_target_properties(lithtech PROPERTIES FOLDER engine)
target_precompile_headers(lithtech PRIVATE shared/bdefs.h)

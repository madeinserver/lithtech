# parents:
# LT_${EX}_SOURCE LT_${EX}_INCLUDE LT_${EX}_LIBDIR LT_${EX}_LIBS LT_${EX}_DEFINE
# ${EX}: SHARED CLIENT SERVER
#

macro(runtime_src DIR EX)
    # root
    file(GLOB ${DIR}_SOURCE "${DIR}/*.cpp" "${DIR}/*.h")
    source_group("${DIR}" FILES ${${DIR}_SOURCE})
    set(${DIR}_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/${DIR}")

    list(APPEND LT_${EX}_SOURCE ${${DIR}_SOURCE})
    list(APPEND LT_${EX}_INCLUDE ${${DIR}_INCLUDE})

    # sys/
    file(GLOB ${DIR}_SYS "${DIR}/sys/*.cpp" "${DIR}/sys/*.h")
    source_group("${DIR}/sys" FILES ${${DIR}_SYS})
    set(${DIR}_SYS_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/${DIR}/sys")

    list(APPEND LT_${EX}_SOURCE ${${DIR}_SYS})
    list(APPEND LT_${EX}_INCLUDE ${${DIR}_SYS_INCLUDE})

    if (WIN32)

        # Windows
        file(GLOB ${DIR}_WIN "${DIR}/sys/win/*.cpp" "${DIR}/sys/win/*.h")
        list(APPEND ${DIR}_WIN_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/${DIR}/sys/win")
        source_group("${DIR}/sys/win" FILES ${${DIR}_WIN})

        list(APPEND LT_${EX}_SOURCE ${${DIR}_WIN})
        list(APPEND LT_${EX}_INCLUDE ${${DIR}_WIN_INCLUDE})

        if ("${LT_RENDER}" STREQUAL "DIRECTX9")
            # DirectX 9
            file(GLOB ${DIR}_D3D "${DIR}/sys/d3d/*.cpp" "${DIR}/sys/d3d/*.h")
            list(APPEND ${DIR}_D3D_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/${DIR}/sys/d3d")
            source_group("${DIR}/sys/d3d" FILES ${${DIR}_D3D})

            list(APPEND LT_${EX}_SOURCE ${${DIR}_D3D})
            list(APPEND LT_${EX}_INCLUDE ${${DIR}_D3D_INCLUDE})
        endif()
    elseif (LINUX)

        # Linux
        file(GLOB ${DIR}_LNX "${DIR}/sys/linux/*.cpp" "${DIR}/sys/linux/*.h")
        list(APPEND ${DIR}_LNX_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/${DIR}/sys/linux")
        source_group("${DIR}/sys/linux" FILES ${${DIR}_LNX})

        list(APPEND LT_${EX}_SOURCE ${${DIR}_LNX})
        list(APPEND LT_${EX}_INCLUDE ${${DIR}_LNX_INCLUDE})
    endif()

    if ("${LT_RENDER}" STREQUAL "OPENGL")
        # OpenGL
        file(GLOB ${DIR}_OGL "${DIR}/sys/ogl/*.cpp" "${DIR}/sys/ogl/*.h")
        list(APPEND ${DIR}_OGL_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/${DIR}/sys/ogl")
        source_group("${DIR}/sys/ogl" FILES ${${DIR}_OGL})

        list(APPEND LT_${EX}_SOURCE ${${DIR}_OGL})
        list(APPEND LT_${EX}_INCLUDE ${${DIR}_OGL_INCLUDE})
    endif()
endmacro()

macro(kernel_src PROJ)
    file(GLOB KRNL_${PROJ}_SOURCE "kernel/${PROJ}/*.cpp" "kernel/${PROJ}/*.h")
    source_group("kernel/${PROJ}" FILES ${KRNL_${PROJ}_SOURCE})
    set(KRNL_${PROJ}_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/kernel/${PROJ}")

    list(APPEND LT_SHARED_SOURCE ${KRNL_${PROJ}_SOURCE})
    list(APPEND LT_SHARED_INCLUDE ${KRNL_${PROJ}_INCLUDE})

    if (WIN32)
        # Windows
        file(GLOB KRNL_${PROJ}_WIN "kernel/${PROJ}/sys/win/*.cpp" "kernel/${PROJ}/sys/win/*.h")
        list(APPEND KRNL_${PROJ}_WIN_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/kernel/${PROJ}/sys/win")
        source_group("kernel/${PROJ}/sys/win" FILES ${KRNL_${PROJ}_WIN})

        list(APPEND LT_SHARED_SOURCE ${KRNL_${PROJ}_WIN})
        list(APPEND LT_SHARED_INCLUDE ${KRNL_${PROJ}_WIN_INCLUDE})
    elseif (LINUX)
        # Linux
        file(GLOB KRNL_${PROJ}_LNX "kernel/${PROJ}/sys/linux/*.cpp" "kernel/${PROJ}/sys/linux/*.h")
        list(APPEND KRNL_${PROJ}_LNX_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/kernel/${PROJ}/sys/linux")
        source_group("kernel/${PROJ}/sys/linux" FILES ${KRNL_${PROJ}_LNX})

        list(APPEND LT_SHARED_SOURCE ${KRNL_${PROJ}_LNX})
        list(APPEND LT_SHARED_INCLUDE ${KRNL_${PROJ}_LNX_INCLUDE})
    endif()

endmacro()

macro(runtime_link PROJ EX)
    target_compile_definitions(${PROJ} PRIVATE ${LT_${EX}_DEFINE})
    target_link_directories(${PROJ} PRIVATE ${LT_${EX}_LIBDIR})
    target_link_libraries(${PROJ} PRIVATE ${LT_${EX}_LIBS})
    target_include_directories(${PROJ} PRIVATE ${LT_${EX}_INCLUDE})
endmacro()

runtime_src(controlfilemgr SHARED)
runtime_src(info SHARED)
runtime_src(lithtemplate SHARED)
runtime_src(model SHARED)
runtime_src(physics SHARED)
runtime_src(render CLIENT)
runtime_src(client CLIENT)
runtime_src(server SHARED)
runtime_src(sound CLIENT)
runtime_src(ui CLIENT)
runtime_src(world SHARED)
runtime_src(shared SHARED)
kernel_src(io)
kernel_src(mem)
kernel_src(net)
kernel_src(src)

if (NOT USE_DIRECTMUSIC)
    list(REMOVE_ITEM LT_SHARED_SOURCE
        kernel/src/sys/win/ltdirectmusic_impl.cpp
        kernel/src/sys/win/ltdirectmusic_impl.h
        kernel/src/sys/win/ltdirectmusiccontrolfile.cpp
        kernel/src/sys/win/ltdirectmusiccontrolfile.h
        kernel/src/sys/win/ltdirectmusicloader.cpp
        kernel/src/sys/win/ltdirectmusicloader.h
    )
else()
    list(APPEND LT_SHARED_DEFINE -DUSE_DIRECTMUSIC)
endif()

if (NOT USE_BINKVIDEO)
    list(REMOVE_ITEM LT_SHARED_SOURCE
        kernel/src/win/binkvideomgrimpl.cpp
        kernel/src/win/binkvideomgrimpl.h
    )
else()
    list(APPEND LT_SHARED_DEFINE -DIHAVEPURCHASEDBINK)
endif()

list(APPEND LT_SHARED_LIBS ltsdk stdlith ltmem lith rezmgr)
list(APPEND LT_CLIENT_LIBS Freetype::Freetype)
list(APPEND LT_CLIENT_SOURCE )
list(APPEND LT_SHARED_DEFINE -DMODEL_SUPPORT_ABC -DUSE_ABSTRACT_SOUND_INTERFACES -DLT15_COMPAT -DNO_PRAGMA_LIBS -DDSNDMGR_NO_MFC -DNO_PRAGMA_LIBS)
list(APPEND LT_SERVER_DEFINE -DSTDLITH_ALLOC_OVERRIDE -DDE_SERVER_COMPILE)
list(APPEND LT_CLIENT_DEFINE -DDE_LOCAL_SERVERBIND -DDE_CLIENT_COMPILE)

if (WIN32)
    set(LT_CLIENT_RESOURCES 
        client/sys/win/idr_main.ico
        client/sys/win/lithtech.rc
        client/sys/win/resource.h
    )
    source_group("resources" FILES ${LT_CLIENT_RESOURCES})

    set(LT_SERVER_RESOURCES
        server/sys/win/server.def
        server/sys/win/server.rc
        server/sys/win/resource.h
    )
    source_group("resources" FILES ${LT_SERVER_RESOURCES})
endif()

if ("${LT_RENDER}" STREQUAL "DIRECTX9")
    list(APPEND LT_CLIENT_LIBS d3dx9 d3d9 dxguid dxerr dinput8 Dbghelp)
    list(APPEND LT_CLIENT_INCLUDE ${DirectX_D3DX9_INCLUDE_DIR})
    list(APPEND LT_CLIENT_LIBDIR ${DirectX_ROOT_DIR}/Lib/${DX_ARCH})

    set(D3D_SHADOWS_SRC
        render/sys/d3d/shadows/d3dmodelshadowrenderer.h
        render/sys/d3d/shadows/d3dshadowtexture.cpp
        render/sys/d3d/shadows/d3dshadowtexture.h
    )
    source_group("render/sys/d3d/shadows" FILES ${D3D_SHADOWS_SRC})
    list(APPEND LT_CLIENT_SOURCE ${D3D_SHADOWS_SRC})
endif()

if (WIN32)
    list(APPEND LT_SHARED_LIBS Winmm ws2_32)
endif()

add_executable(lithtech WIN32 ${LT_SHARED_SOURCE} ${LT_CLIENT_SOURCE} ${LT_CLIENT_RESOURCES})
runtime_link(lithtech SHARED)
runtime_link(lithtech CLIENT)
set_target_properties(lithtech PROPERTIES FOLDER engine)
target_precompile_headers(lithtech PRIVATE shared/bdefs.h)

add_library(server ${LT_SHARED_SOURCE} ${LT_SERVER_SOURCE} ${LT_SERVER_RESOURCES})
runtime_link(server SHARED)
runtime_link(server SERVER)
set_target_properties(server PROPERTIES FOLDER engine)
target_precompile_headers(server PRIVATE bdefs.h)

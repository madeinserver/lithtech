

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
    elseif (LINUX)

        # Linux
        file(GLOB ${DIR}_LNX "${DIR}/sys/linux/*.cpp" "${DIR}/sys/linux/*.h")
        list(APPEND ${DIR}_LNX_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/${DIR}/sys/linux")
        source_group("${DIR}/sys/linux" FILES ${${DIR}_LNX})

        list(APPEND LT_${EX}_SOURCE ${${DIR}_LNX})
        list(APPEND LT_${EX}_INCLUDE ${${DIR}_LNX_INCLUDE})
    endif()
endmacro()

macro(kernel_src PROJ EX)
    file(GLOB KRNL_${PROJ}_SOURCE "kernel/${PROJ}/*.cpp" "kernel/${PROJ}/*.h")
    source_group("kernel/${PROJ}" FILES ${KRNL_${PROJ}_SOURCE})
    set(KRNL_${PROJ}_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/kernel/${PROJ}")

    list(APPEND LT_${EX}_SOURCE ${KRNL_${PROJ}_SOURCE})
    list(APPEND LT_${EX}_INCLUDE ${KRNL_${PROJ}_INCLUDE})

    if (WIN32)
        # Windows
        file(GLOB KRNL_${PROJ}_WIN "kernel/${PROJ}/sys/win/*.cpp" "kernel/${PROJ}/sys/win/*.h")
        list(APPEND KRNL_${PROJ}_WIN_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/kernel/${PROJ}/sys/win")
        source_group("kernel/${PROJ}/sys/win" FILES ${KRNL_${PROJ}_WIN})

        list(APPEND LT_${EX}_SOURCE ${KRNL_${PROJ}_WIN})
        list(APPEND LT_${EX}_INCLUDE ${KRNL_${PROJ}_WIN_INCLUDE})
    elseif (LINUX)
        # Linux
        file(GLOB KRNL_${PROJ}_LNX "kernel/${PROJ}/sys/linux/*.cpp" "kernel/${PROJ}/sys/linux/*.h")
        list(APPEND KRNL_${PROJ}_LNX_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/kernel/${PROJ}/sys/linux")
        source_group("kernel/${PROJ}/sys/linux" FILES ${KRNL_${PROJ}_LNX})

        list(APPEND LT_${EX}_SOURCE ${KRNL_${PROJ}_LNX})
        list(APPEND LT_${EX}_INCLUDE ${KRNL_${PROJ}_LNX_INCLUDE})
    endif()

endmacro()

macro(runtime_link PROJ EX)
    target_compile_definitions(${PROJ} PRIVATE ${LT_${EX}_DEFINE})
    target_link_directories(${PROJ} PRIVATE ${LT_${EX}_LIBDIR})
    target_link_libraries(${PROJ} PRIVATE ${LT_${EX}_LIBS})
    target_include_directories(${PROJ} PRIVATE ${LT_${EX}_INCLUDE})
endmacro()

set(LT_SHARED_LIBS ltsdk stdlith ltmem lith rezmgr dtxmgr)

if (WIN32)
    list(APPEND LT_SHARED_LIBS Winmm ws2_32 Dbghelp)
endif()

set(LT_SHARED_DEFINE -DMODEL_SUPPORT_ABC -DUSE_ABSTRACT_SOUND_INTERFACES -DLT15_COMPAT -DNO_PRAGMA_LIBS -DDSNDMGR_NO_MFC -DNO_PRAGMA_LIBS)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}")

include(Client)
include(Server)

macro(add_dir PROJ)
    file(GLOB ${PROJ}_SRC "${PROJ}/*.cpp" "${PROJ}/*.h")
    source_group("${PROJ}" FILES ${${PROJ}_SRC})
    list(APPEND TOOLS_INC ${CMAKE_CURRENT_LIST_DIR}/${PROJ})

    if (WIN32)
        file(GLOB ${PROJ}_WIN "{PROJ}/sys/win/*.cpp" "${PROJ}/sys/win/*.h")
        source_group("${PROJ}/sys/win" FILES ${${PROJ}_WIN})
    endif()

    list(APPEND TOOLS_SRC ${${PROJ}_WIN})
    list(APPEND TOOLS_SRC ${${PROJ}_SRC})
endmacro()

add_dir(engine)
add_dir(model)
add_dir(packer)
add_dir(world)

add_library(lttools STATIC ${TOOLS_SRC})
target_include_directories(lttools PUBLIC ${TOOLS_INC} .)
set_target_properties(lttools PROPERTIES FOLDER libs)
target_link_libraries(lttools PUBLIC ltsdk stdlith ltamgr dibmgr dtxmgr s3tc aegis)
target_link_directories(lttools PRIVATE ${DirectX_ROOT_DIR}/Lib/${DX_ARCH})
target_compile_definitions(lttools PUBLIC -DDIRECTEDITOR_BUILD -DPRE_FLOAT -DLT15_COMPAT -DNO_PRAGMA_LIBS -DSTDLITH_MFC -DBDEFS_MFC)

if (USE_DIRECTMUSIC)
    target_compile_definitions(lttools PUBLIC -DUSE_DIRECTMUSIC)
endif()

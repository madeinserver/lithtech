macro(my_install TARGET TYPE DEST COMPONENT)
    install(TARGETS ${TARGET} CONFIGURATIONS "RelWithDebInfo" ${TYPE} DESTINATION ${DEST} COMPONENT ${COMPONENT})
    
    if (NOT "${TYPE}" STREQUAL "ARCHIVE")
        install(FILES $<TARGET_PDB_FILE:${TARGET}> CONFIGURATIONS "RelWithDebInfo" DESTINATION ${DEST} COMPONENT ${COMPONENT} OPTIONAL)
    endif()
endmacro()

macro(my_install_engine TARGET COMPONENT SUFFIX)
    install(TARGETS ${TARGET} CONFIGURATIONS "RelWithDebInfo" COMPONENT ${COMPONENT} 
        RUNTIME DESTINATION bin${SUFFIX}
        LIBRARY DESTINATION bin${SUFFIX}
        ARCHIVE DESTINATION lib${SUFFIX}
    )

    install(TARGETS ${TARGET} CONFIGURATIONS "Debug" COMPONENT ${COMPONENT} 
        RUNTIME DESTINATION bin${SUFFIX}/debug
        LIBRARY DESTINATION bin${SUFFIX}/debug
        ARCHIVE DESTINATION lib${SUFFIX}/debug
    )
endmacro()

macro(my_install_engine_pdb TARGET COMPONENT SUFFIX)
    install(FILES $<TARGET_PDB_FILE:${TARGET}> CONFIGURATIONS "RelWithDebInfo" DESTINATION bin${SUFFIX} COMPONENT ${COMPONENT} OPTIONAL)
    install(FILES $<TARGET_PDB_FILE:${TARGET}> CONFIGURATIONS "Debug" DESTINATION bin${SUFFIX}/debug COMPONENT ${COMPONENT} OPTIONAL)
endmacro()

# install the engine
my_install_engine(lithtech Runtime "")
my_install_engine(server Runtime "")
my_install_engine(ltmsg Runtime "")
my_install_engine(ltsdk Development "")
my_install_engine_pdb(lithtech Runtime "")
my_install_engine_pdb(server Runtime "")
my_install_engine_pdb(ltmsg Runtime "")

if (WIN32)
    # Defualt is dx on Windows
    my_install_engine(SoundDx8 Runtime "")
    my_install_engine_pdb(SoundDx8 Runtime "")
    my_install_engine(RenderDx9 Runtime "")
    my_install_engine_pdb(RenderDx9 Runtime "")
endif()

my_install_engine(SoundNull Runtime "/nulldrv")
my_install_engine_pdb(SoundNull Runtime "/nulldrv")
my_install_engine(RenderNull Runtime "/nulldrv")
my_install_engine_pdb(RenderNull Runtime "/nulldrv")

# install tools
if (NOT LT_NO_TOOLS)
    my_install(ButeEdit RUNTIME tools Tools)
    #my_install(DEdit RUNTIME tools Tools)
    #my_install(DtxShellEx LIBRARY tools Tools)
    my_install(dtxutil RUNTIME tools Tools)
    #my_install(DtxView RUNTIME tools Tools)
    #my_install(FxED RUNTIME tools Tools)
    my_install(HeightMaptoNormalMap RUNTIME tools Tools)
    my_install(lipcompiler RUNTIME tools Tools)
    my_install(lithrez RUNTIME tools Tools)
    my_install(LTAsk RUNTIME tools Tools)
    my_install(ltaview RUNTIME tools Tools)
    my_install(ltbhead RUNTIME tools Tools)
    my_install(LTC RUNTIME tools Tools)
    my_install(Model_Packer RUNTIME tools Tools)
    #my_install(ModelEdit RUNTIME tools Tools)
    my_install(pma RUNTIME tools Tools)
    my_install(PropHelpGen RUNTIME tools Tools)
    my_install(recurse_run RUNTIME tools Tools)
    my_install(RenderStyleEditor RUNTIME tools Tools)
    my_install(RenderStylePacker RUNTIME tools Tools)
    my_install(RenderStyleViewer RUNTIME tools Tools)
    #my_install(SetVersionCode RUNTIME tools Tools) #internal tool
    my_install(TSCompiler RUNTIME tools Tools)
    my_install(WaveEdit RUNTIME tools Tools)
    my_install(WinLTC RUNTIME tools Tools)
    my_install(winpacker RUNTIME tools Tools)
    my_install(WorldPacker RUNTIME tools Tools)
endif()

# install the sdk
install(DIRECTORY ${CMAKE_SOURCE_DIR}/sdk/inc DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/sdk/rez DESTINATION .)
install(FILES ${CMAKE_SOURCE_DIR}/sdk/Legal.txt DESTINATION .)

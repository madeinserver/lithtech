add_subdirectory(lith)
add_subdirectory(stdlith)
add_subdirectory(CryptMgr)
add_subdirectory(ButeMgr)
add_subdirectory(rezmgr)
add_subdirectory(ltamgr)
add_subdirectory(ltmem)
add_subdirectory(dibmgr)
add_subdirectory(dtxmgr)
add_subdirectory(libsquish)
add_subdirectory(aegis)
add_subdirectory(lttool)
add_subdirectory(genregmgr)
set_target_properties(squish PROPERTIES FOLDER "libs")

if (WIN32)
    add_subdirectory(RegMgr32)
    add_subdirectory(RegMgr)
endif()

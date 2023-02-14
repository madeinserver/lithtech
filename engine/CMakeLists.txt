add_subdirectory(runtime)
add_subdirectory(ltmsg)
add_subdirectory(sound_null)

if (WIN32)
    add_subdirectory(sound_dx8)
endif()

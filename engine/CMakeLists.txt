add_subdirectory(runtime)
add_subdirectory(ltmsg)
add_subdirectory(sound_null)
add_subdirectory(render_null)

if (WIN32)
    add_subdirectory(sound_dx8)
    add_subdirectory(render_dx9)
endif()

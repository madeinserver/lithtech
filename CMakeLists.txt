# lithtech
cmake_minimum_required(VERSION 3.20)
project(Lithtech)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake")

if (MSVC)
    set(LT_FLAGS "/utf-8 /MP")
else() # GCC/CLang
    set(LT_FLAGS "-fpermissive")
endif()

string(FIND ${VCPKG_TARGET_TRIPLET} "-static" IS_STATIC)

if (NOT "${IS_STATIC}" STREQUAL "-1") # /MT
    set(IS_STATIC 1)
    set(CMAKE_MFC_FLAG 1)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "MSVC Runtime library" FORCE)
else() # /MD
    set(IS_STATIC 0)
    set(CMAKE_MFC_FLAG 2)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LT_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LT_FLAGS}")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS64 1)
    set(DX_ARCH x64)
else()
    set(BITS64 0)
    set(DX_ARCH x86)
endif()

if(WIN32)
    find_package(DirectX REQUIRED)
    set(LT_RENDER "DIRECTX9")
elseif(UNIX AND NOT APPLE)
    set(LINUX 1)
    set(LT_RENDER "OPENGL")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

find_package(ZLIB REQUIRED)
find_package(Freetype REQUIRED)

# release: _FINAL
# unknown: _PUBLIC_DEVELOPMENT

add_subdirectory(sdk)
add_subdirectory(libs)
add_subdirectory(engine)

if (NOT LT_NO_TOOLS)
    add_subdirectory(tools)
endif()

if (NOT LT_NO_INSTALL)
    include(MakeSDK)
endif()

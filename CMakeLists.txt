# lithtech
cmake_minimum_required(VERSION 3.20)
project(Lithtech)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake")

if (MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8 /MP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /MP")
endif()

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
# demo: COMPILE_JUPITER_EVAL

add_subdirectory(sdk)
add_subdirectory(libs)
add_subdirectory(engine)

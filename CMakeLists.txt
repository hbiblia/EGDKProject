# new version
cmake_minimum_required(VERSION 3.12)

project(EGDKProject)
set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(Engine/Source/Ermine/include)
include_directories(Engine/Source/ThirdParty)

# 
if(CMAKE_SYSTEM_NAME STREQUAL Windows OR CMAKE_SYSTEM_NAME MATCHES "MINGW64_NT")
    message("** Windows Build D3D11 **")

    add_compile_definitions(SOKOL_D3D11)
    add_compile_definitions(WINDOWS)
    set(EGDK_PLATFORM WINDOWS)
    set(EGDK_LIBS ${EGDK_LIBS} 
        kernel32
        user32
        shell32 
        dxgi 
        d3d11 
        ole32 
        gdi32)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    message("** Linux Build GL33 **")

    add_compile_definitions(SOKOL_GLCORE33)
    set(EGDK_PLATFORM LINUX)
    set(EGDK_LIBS ${EGDK_LIBS} 
        GL 
        dl 
        m 
        X11 
        asound 
        Xi 
        Xcursor 
        pthread)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    message("** Darwin Build Metal **")

    set(EGDK_PLATFORM DARWIN)
endif()

# 
add_subdirectory(Engine/Source/Ermine)
add_subdirectory(Engine/Source/Editor)
add_subdirectory(Engine/Source/Game)
add_subdirectory(Engine/Source/ThirdParty/cimgui)
add_subdirectory(Engine/Source/ThirdParty/flecs)
add_subdirectory(Engine/Source/ThirdParty/parson)
add_subdirectory(Engine/Source/ThirdParty/sokol)
add_subdirectory(Engine/Source/ThirdParty/stb)
add_subdirectory(Engine/Source/ThirdParty/array_dynamic)

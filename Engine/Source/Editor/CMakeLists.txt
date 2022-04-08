# EDITOR

set(SOUCE_EDITOR
    src/main.c
    src/editor.c
    src/panel_assets.c
    src/panel_hierarchy.c
    src/panel_inspector.c
    src/panel_viewport.c
    src/custom-imgui.c
)

# PKG_CONFIG
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

if(EGDK_PLATFORM STREQUAL WINDOWS)
    set(EDITOR_LIBS kernel32 user32 shell32 dxgi d3d11 ole32 gdi32 Ws2_32)
    add_definitions(-IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -mms-bitfields -IC:/msys64/mingw64/include)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    set(EDITOR_LIBS GL dl m X11 asound Xi Xcursor pthread)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()

list(APPEND EDITOR_LIBS Ermine)

add_compile_definitions(USE_LIBTYPE_SHARED)

add_executable(EGDKEditor ${SOUCE_EDITOR})
target_link_libraries(EGDKEditor ${EDITOR_LIBS})

if(CMAKE_SYSTEM_NAME STREQUAL WINDOWS)
    target_compile_options(EGDKEditor PRIVATE /W3)
elseif(CMAKE_SYSTEM_NAME STREQUAL LINUX)
    target_compile_options(EGDKEditor PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_SYSTEM_NAME STREQUAL DARWIN)
endif()
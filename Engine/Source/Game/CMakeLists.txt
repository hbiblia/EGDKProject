# EDITOR

set(SOUCE_EDITOR
    src/main.c
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

add_executable(EGDKGame ${SOUCE_EDITOR})

target_link_libraries(EGDKGame ${EDITOR_LIBS})

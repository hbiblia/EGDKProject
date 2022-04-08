

# ERMINE LIBS
set(SOUCE_ERMINE
    src/ermine-util.c
    src/ermine-assets-manager.c
    src/ermine-resource.c
    src/ermine-window.c
    src/ermine-shape.c
    src/ermine-texture.c
    src/ermine-color.c
    src/ermine-render.c
    src/ermine-input.c
    src/ermine-scene.c
    src/ermine-camera.c
    src/ermine-math.c
    src/ermine-flower.c

    src/Components/component.base.c
    src/Components/TransformComponent.c
    src/Components/SpriteRendererComponent.c
    src/Components/AnimateSpriteComponent.c
    src/Components/DamageComponent.c
    src/Components/InfoComponent.c
)

set(ERMINE_DEPS
    cimgui
    flecs
    parson
    sokol
    stb
)

# PKG_CONFIG
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

if(EGDK_PLATFORM STREQUAL WINDOWS)
    set(ERMINE_DEPS ${ERMINE_DEPS} kernel32 user32 shell32 dxgi d3d11 ole32 gdi32 Ws2_32)
    # MIN64
    add_definitions(-IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -mms-bitfields -IC:/msys64/mingw64/include)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    set(ERMINE_DEPS ${ERMINE_DEPS} GL dl m X11 asound Xi Xcursor pthread Ws2_32)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()

add_compile_definitions(BUILD_LIBTYPE_SHARED)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_library(Ermine SHARED ${SOUCE_ERMINE})

target_link_libraries(Ermine PRIVATE ${ERMINE_DEPS} ${GLIB_LIBRARIES})

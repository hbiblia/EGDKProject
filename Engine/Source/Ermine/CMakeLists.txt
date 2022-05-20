

# ERMINE LIBS
set(SOUCE_ERMINE
    src/ermine-core.c
    src/ermine-ecs.c
    src/ermine-window.c
    src/ermine-gfx-renderer.c
    src/ermine-string.c
    src/ermine-path.c
    src/ermine-file.c
    src/ermine-resource.c
    src/ermine-ui.c
    src/ermine-camera.c
    src/ermine-dialog.c
    src/ermine-math.c
    # Component base
    src/ermine-crenderer.c
    src/ermine-ccolor.c
    src/ermine-cshapes.c
    src/ermine-cmath.c
    src/ermine-ctransform.c
    src/ermine-ctexture.c
    src/ermine-cbaseinfo.c

    src/ermine-c-background.c
)

set(ERMINE_DEPS
    stb
    parson
    flecs
    sokol
    cimgui
    # nuklear
)

# FIX BUG MSYS2
set(multipledefinition -Wl,--allow-multiple-definition)
set(CXX_FLAGS -DBUILD_LIBTYPE_SHARED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

add_library(Ermine SHARED ${SOUCE_ERMINE})

target_link_libraries(Ermine PRIVATE ${ERMINE_DEPS} ${EGDK_LIBS} ${GLIB_LIBRARIES} ${multipledefinition})

target_include_directories(Ermine PRIVATE ${GLIB_INCLUDE_DIRS})

target_compile_options(Ermine PRIVATE ${CXX_FLAGS})

if(EGDK_PLATFORM STREQUAL WINDOWS)
    # VS
    # target_compile_options(Ermine PRIVATE /W3)
    # MSYS2
    target_compile_options(Ermine PRIVATE -w -Wall -Wextra -Wpedantic)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    target_compile_options(Ermine PRIVATE -Wall -Wextra -Wpedantic)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()
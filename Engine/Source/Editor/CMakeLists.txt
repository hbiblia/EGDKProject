# EDITOR

set(SOUCE_EDITOR
    src/main.c
    src/editor-internal.c
    src/panel_assets.c
    src/panel_hierarchy.c
    src/panel_inspector.c
    src/panel_viewport.c
    src/custom-imgui.c
)

set(ERMINE_DEPS
    cimgui
    flecs
    parson
    sokol
    stb
    array_dynamic
    Ermine
)

add_executable(EGDKEditor ${SOUCE_EDITOR})
target_link_libraries(EGDKEditor PRIVATE ${EGDK_LIBS} ${ERMINE_DEPS})

if(EGDK_PLATFORM STREQUAL WINDOWS)
    target_compile_options(EGDKEditor PRIVATE /W3)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    target_compile_options(EGDKEditor PRIVATE -Wall -Wextra -Wpedantic)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()
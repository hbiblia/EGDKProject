# EDITOR

set(SOUCE_EDITOR
    src/main.c
    src/editor_data.c
    src/ui_editor_main.c
    src/ui_editor_menubar.c
    src/ui_docked_hierarchy.c
    src/ui_docked_inspector.c

    src/editor-internal.c
    src/panel_assets.c
    # src/panel_hierarchy.c
    # src/panel_inspector.c
    src/panel_viewport.c
    src/custom-imgui.c
)

set(ERMINE_DEPS
    Ermine
    parson
    flecs
)

set(CXX_FLAGS -DUSE_LIBTYPE_SHARED)

add_executable(EGDKEditor ${SOUCE_EDITOR})
target_link_libraries(EGDKEditor PRIVATE ${EGDK_LIBS} ${ERMINE_DEPS})
target_compile_options(EGDKEditor PRIVATE ${CXX_FLAGS})

if(EGDK_PLATFORM STREQUAL WINDOWS)
    # target_compile_options(EGDKEditor PRIVATE /W3)
    target_compile_options(EGDKEditor PRIVATE -Wall -Wextra -Wpedantic)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    target_compile_options(EGDKEditor PRIVATE -Wall -Wextra -Wpedantic)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()
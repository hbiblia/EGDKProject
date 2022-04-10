

# ERMINE LIBS
set(SOUCE_ERMINE
    src/ermine-util.c
    src/ermine-assets-manager.c
    src/ermine-resource.c
    src/ermine-window.c
    src/ermine-shape.c
    src/ermine-texture.c
    src/ermine-color.c
    src/ermine-renderer.c
    src/ermine-input.c
    src/ermine-scene.c
    src/ermine-camera.c
    src/ermine-math.c
    src/ermine-flower.c
    src/ermine-hash.c

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
    array_dynamic
    Ermine
)

add_library(Ermine SHARED ${SOUCE_ERMINE})
target_link_libraries(Ermine PRIVATE ${ERMINE_DEPS} ${EGDK_LIBS})

if(EGDK_PLATFORM STREQUAL WINDOWS)
    target_compile_options(Ermine PRIVATE /W3)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    target_compile_options(Ermine PRIVATE -Wall -Wextra -Wpedantic)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()
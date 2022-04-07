cmake_minimum_required(VERSION 3.22)

project(EGDKProject)

set(CMAKE_C_STANDARD 99)

# ERMINE LIBS
set(SOUCE_ERMINE
Engine/Source/Ermine/ermine-util.c
Engine/Source/Ermine/ermine-assets-manager.c
Engine/Source/Ermine/ermine-resource.c
Engine/Source/Ermine/ermine-window.c
Engine/Source/Ermine/ermine-shape.c
Engine/Source/Ermine/ermine-texture.c
Engine/Source/Ermine/ermine-color.c
Engine/Source/Ermine/ermine-render.c
Engine/Source/Ermine/ermine-input.c
Engine/Source/Ermine/ermine-scene.c
Engine/Source/Ermine/ermine-camera.c
Engine/Source/Ermine/ermine-math.c
Engine/Source/Ermine/ermine-flower.c

Engine/Source/ThirdParty/flecs/flecs.c
Engine/Source/ThirdParty/parson/parson.c

Engine/Source/Components/component.base.c
Engine/Source/Components/TransformComponent.c
Engine/Source/Components/SpriteRendererComponent.c
Engine/Source/Components/AnimateSpriteComponent.c
Engine/Source/Components/DamageComponent.c
Engine/Source/Components/InfoComponent.c
)

# EDITOR
set(SOUCE_EDITOR
Engine/Source/Editor/main.c
Engine/Source/Editor/panel_assets.c
Engine/Source/Editor/panel_hierarchy.c
Engine/Source/Editor/panel_inspector.c
Engine/Source/Editor/panel_viewport.c
Engine/Source/Editor/editor.c
Engine/Source/Editor/custom-imgui.c
)

# GAME
set(SOUCE_GAME
Engine/Source/Game/main.c
)

if(${CMAKE_SYSTEM_NAME} MATCHES "MINGW64_NT")
    add_definitions(-DSOKOL_D3D11)
    set(LINK_RENDER -lkernel32 -luser32 -lshell32 -ldxgi -ld3d11 -lole32 -lgdi32 -lcimgui -lWs2_32)
    # En windows con Msys2 estaba dando problema
    add_definitions(-IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -mms-bitfields -IC:/msys64/mingw64/include )
    message("Windows Build")
endif()
    
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DSOKOL_GLCORE33)
    set(LINK_RENDER -lGL -ldl -lm -lX11 -lasound -lXi -lXcursor -lcimgui)
    message("Linux Build")
endif()

# PKG_CONFIG
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS} Engine/Source/Ermine/ Engine/Source/ThirdParty/ Engine/Source/Components/)
link_directories(${GLIB_LIBRARY_DIRS} Engine/Source/ThirdParty/cimgui)

add_executable(EGDKEditor ${SOUCE_ERMINE} ${SOUCE_EDITOR})
target_link_libraries(EGDKEditor PUBLIC ${LINK_RENDER} -lcimgui -lWs2_32 ${GLIB_LIBRARIES})


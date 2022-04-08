# cmake_minimum_required(VERSION 3.22)

# project(EGDKProject)
# set(CMAKE_C_STANDARD 99)

# # ERMINE LIBS
# set(SOUCE_ERMINE
# Engine/Source/Ermine/ermine-util.c
# Engine/Source/Ermine/ermine-assets-manager.c
# Engine/Source/Ermine/ermine-resource.c
# Engine/Source/Ermine/ermine-window.c
# Engine/Source/Ermine/ermine-shape.c
# Engine/Source/Ermine/ermine-texture.c
# Engine/Source/Ermine/ermine-color.c
# Engine/Source/Ermine/ermine-render.c
# Engine/Source/Ermine/ermine-input.c
# Engine/Source/Ermine/ermine-scene.c
# Engine/Source/Ermine/ermine-camera.c
# Engine/Source/Ermine/ermine-math.c
# Engine/Source/Ermine/ermine-flower.c

# Engine/Source/ThirdParty/flecs/flecs.c
# Engine/Source/ThirdParty/parson/parson.c

# Engine/Source/Components/component.base.c
# Engine/Source/Components/TransformComponent.c
# Engine/Source/Components/SpriteRendererComponent.c
# Engine/Source/Components/AnimateSpriteComponent.c
# Engine/Source/Components/DamageComponent.c
# Engine/Source/Components/InfoComponent.c
# )

# # EDITOR
# set(SOUCE_EDITOR
# Engine/Source/Editor/main.c
# Engine/Source/Editor/panel_assets.c
# Engine/Source/Editor/panel_hierarchy.c
# Engine/Source/Editor/panel_inspector.c
# Engine/Source/Editor/panel_viewport.c
# Engine/Source/Editor/editor.c
# Engine/Source/Editor/custom-imgui.c
# )

# # GAME
# set(SOUCE_GAME
# Engine/Source/Game/main.c
# )

# if(${CMAKE_SYSTEM_NAME} MATCHES "MINGW64_NT")
# add_definitions(-DSOKOL_D3D11)
# set(LINK_RENDER kernel32 user32 shell32 dxgi d3d11 ole32 gdi32 Ws2_32)
# set(CIMGUI_LIBRARIES cimgui.dll)
# # En windows con Msys2 estaba dando problema
# add_definitions(-IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -mms-bitfields -IC:/msys64/mingw64/include )
# message("** Windows Build D3D11 **")
# endif()

# if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# add_definitions(-DSOKOL_GLCORE33)
# set(LINK_RENDER GL dl m X11 asound Xi Xcursor pthread)
# set(CIMGUI_LIBRARIES -lcimgui)
# message("** Linux Build GL33 **")
# endif()

# # PKG_CONFIG
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(GLIB REQUIRED glib-2.0)

# # make ermine && make game && make editor
# include_directories(${GLIB_INCLUDE_DIRS} Engine/Source/Ermine/ Engine/Source/ThirdParty/ Engine/Source/Components/)
# link_directories(${GLIB_LIBRARY_DIRS} Engine/Source/ThirdParty/cimgui/)

# add_executable(EGDKEditor ${SOUCE_ERMINE} ${SOUCE_EDITOR})
# target_link_libraries(EGDKEditor PUBLIC ${LINK_RENDER} ${GLIB_LIBRARIES} ${CIMGUI_LIBRARIES})


# new version

cmake_minimum_required(VERSION 3.12)

project(EGDKProject)
set(CMAKE_C_STANDARD 99)

message(${CMAKE_SYSTEM_NAME})

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(Engine/Source/Ermine/src)
include_directories(Engine/Source/ThirdParty)

if(CMAKE_SYSTEM_NAME STREQUAL Windows OR CMAKE_SYSTEM_NAME MATCHES "MINGW64_NT")
    message("** Windows Build D3D11 **")

    add_compile_definitions(SOKOL_D3D11)
    add_compile_definitions(WINDOWS)
    set(EGDK_PLATFORM WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
    message("** Linux Build GL33 **")

    set(EGDK_PLATFORM LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    message("** Darwin Build Metal **")

    set(EGDK_PLATFORM DARWIN)
endif()

add_subdirectory(Engine/Source/Ermine)
add_subdirectory(Engine/Source/Editor)
add_subdirectory(Engine/Source/Game)

add_subdirectory(Engine/Source/ThirdParty/cimgui)
add_subdirectory(Engine/Source/ThirdParty/flecs)
add_subdirectory(Engine/Source/ThirdParty/parson)
add_subdirectory(Engine/Source/ThirdParty/sokol)
add_subdirectory(Engine/Source/ThirdParty/stb)
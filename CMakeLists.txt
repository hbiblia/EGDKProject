cmake_minimum_required(VERSION 3.22)

project(EGDKProject)

set(CMAKE_CXX_STANDARD 11)

# PKG_CONFIG
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

# ERMINE LIBS
set(SOUCE_ERMINE
Engine/Source/Ermine/ewindow.c
Engine/Source/Ermine/eresource.c
Engine/Source/Ermine/etexture.c
Engine/Source/Ermine/esprite.c
Engine/Source/Ermine/escripts.c
Engine/Source/Ermine/ecolor.c
Engine/Source/Ermine/eutil.c
Engine/Source/Ermine/erender.c
Engine/Source/Ermine/eshape.c
Engine/Source/Ermine/einput.c
Engine/Source/Ermine/eanimate.c
Engine/Source/Ermine/eactor.c
Engine/Source/ThirdParty/flecs/flecs.c
Engine/Source/ThirdParty/parson/parson.c
Engine/Source/Ermine/component.transform.c
Engine/Source/Ermine/component.sprites.c
)

# EDITOR
set(SOUCE_EDITOR
Engine/Source/Editor/main.c
Engine/Source/Editor/panel_assets.c
Engine/Source/Editor/panel_hierarchy.c
Engine/Source/Editor/panel_inspector.c
Engine/Source/Editor/panel_viewport.c
)

# GAME
set(SOUCE_GAME
Engine/Source/Game/main.c
)

set(LINK_RENDER -lkernel32 -luser32 -lshell32 -lgdi32 -lole32 -lcimgui -lWs2_32)

add_definitions(-DSOKOL_GLCORE33)
add_definitions(-IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -mms-bitfields -IC:/msys64/mingw64/include )

include_directories(${GLIB_INCLUDE_DIRS} Engine/Source/Ermine/ Engine/Source/ThirdParty/)
link_directories(${GLIB_LIBRARY_DIRS} Engine/Source/ThirdParty/cimgui)

add_executable(EGDKEditor ${SOUCE_ERMINE} ${SOUCE_EDITOR})
target_link_libraries(EGDKEditor PUBLIC ${LINK_RENDER} -lcimgui -lWs2_32 ${GLIB_LIBRARIES})


#!/bin/bash


# ERMINE
ERMINE_SRC="Engine/Source/Ermine/ewindow.c"

# EDITOR
EDITOR_SRC="Engine/Source/Editor/main.c"

# Game
GAME_SRC="Engine/Source/Game/main.c"

FLAGS="-DSOKOL_GLCORE33"
INCLUDES="-IEngine/Source/Ermine/ -IEngine/Source/ThirdParty/"
LIBS="-lkernel32 -luser32 -lshell32 -lgdi32 -lole32 -lcimgui"
DIRECTORY_LIBS="-LEngine/Source/ThirdParty/cimgui"

# Create folder build
mkdir -p build

# Create cimgui y copiamos los archivos
make -C Engine/Source/ThirdParty/cimgui/
cp Engine/Source/ThirdParty/cimgui/cimgui.dll build/

# BUILD
gcc $ERMINE_SRC $EDITOR_SRC -o build/EGDKEditor $FLAGS $DIRECTORY_LIBS $LIBS $INCLUDES
gcc $ERMINE_SRC $GAME_SRC -o build/EGDKGame $FLAGS $DIRECTORY_LIBS $LIBS $INCLUDES


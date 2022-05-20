#include <stdio.h>
#include "ermine-core.h"
#include "ermine-window.h"

#include "ui_editor_main.h"

#define version "EGDKEditor v1.0-dev"

int main(int argc, char *argv[])
{
    ermine_init(argc, argv);

    // WINDOW
    ermine_window_new(version, 1280, 700);

    ermine_window_fn_init(editor_main_init);
    ermine_window_fn_renderer(editor_main_render);

    ermine_main();
}

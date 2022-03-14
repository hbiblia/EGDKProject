#include <stdio.h>

// #define CIMGUI_IMPL
#include "ermine.h"

void update()
{
    // igText("Hello, world!");
}

int main(int argc, char *argv[])
{
    printf("EGDKGame v1.0-dev \n");

    ewindow_init((ewindow_desc){
        .title = "EGDKEGame - none",
        .width = 1024,
        .height = 768,
        .update_fn = update,
    });
}
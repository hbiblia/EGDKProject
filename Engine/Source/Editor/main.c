#include <stdio.h>

#define CIMGUI_IMPL
#include "ermine.h"

void update()
{
    igSetNextWindowPos((ImVec2){10,10}, ImGuiCond_Once, (ImVec2){0,0});
    igSetNextWindowSize((ImVec2){400, 100}, ImGuiCond_Once);
    igBegin("Hello Dear ImGui!", 0, ImGuiWindowFlags_None);
    igText("Hello, world!");
    igEnd();
}

int main(int argc, char *argv[])
{
    printf("EGDKEditor v1.0-dev \n");

    ewindow_init((ewindow_desc){
        .title = "EGDKEditor - none",
        .width = 1024,
        .height = 768,
        .update_fn = update,
    });
}
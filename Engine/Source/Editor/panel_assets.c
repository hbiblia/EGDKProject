#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <eactor.h>

void panel_assets_main(void)
{
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Assets", false, ImGuiWindowFlags_NoMove))
    {
    }
    igEnd();
}

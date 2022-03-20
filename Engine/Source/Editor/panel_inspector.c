#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <eactor.h>

#include "editor.h"
#include <glib.h>

void panel_inspector_main(void)
{
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Inspector", false, ImGuiWindowFlags_NoMove))
    {
        const char *name = hierarchy_get_selected();
        igText(g_strdup_printf("Actor Selected: %s", name));
    }
    igEnd();
}

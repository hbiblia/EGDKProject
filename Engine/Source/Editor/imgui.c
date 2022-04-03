#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <ermine-flower.h>

#include "imgui.h"

static int popup_queue = 0;

// ------------------------
// Popup
// ------------------------
void imgui_OpenPopup(const char *id)
{
    if(popup_queue == 1){
        igEndPopup();
        popup_queue = 2;
    }
    igOpenPopup_Str(id, 0);
}

bool imgui_BeginPopup(const char *str_id)
{
    bool result = igBeginPopup(str_id, ImGuiWindowFlags_Popup);
    popup_queue = result ? 1 : 0;
    return result;
}

bool imgui_BeginPopupModal(const char *str_id)
{
    bool result = igBeginPopupModal(str_id, NULL, 0);
    popup_queue = result ? 1 : 0;
    return result;
}

bool imgui_BeginPopupContextItem(const char* str_id,ImGuiPopupFlags popup_flags)
{
    bool result = igBeginPopupContextItem(str_id, popup_flags);
    popup_queue = result ? 1 : 0;
    return result;
}

void imgui_EndPopup(void)
{
    if(popup_queue == 1){
        igEndPopup();
    }
    popup_queue = 0;
}

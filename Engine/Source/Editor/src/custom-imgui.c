#include "custom-imgui.h"
#include "ermine-string.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

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

bool imgui_BeginPopupContextItem(const char* str_id, int popup_flags)
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

// ------------------------
// Prop label
// ------------------------ 

void imgui_labelPropBegin(const char *label, int id)
{
    igColumns(2, 0, false);
    igSetColumnWidth(0, 100.0f);
    igTextWrapped(label);
    igNextColumn();
    igPushItemWidth(-1);
    igPushID_Int(id);
    // igPushID_Str(ermine_strdup_printf("%s%d\n",label,id));
}

void imgui_labelPropEnd(void)
{
    igPopID();
    igColumns(1, 0, false);
}

#include <stdio.h>

// ------------------------
// Popup
// ------------------------

void imgui_OpenPopup(const char *id);

bool imgui_BeginPopup(const char* str_id);

bool imgui_BeginPopupModal(const char* str_id);

bool imgui_BeginPopupContextItem(const char* str_id,ImGuiPopupFlags popup_flags);

void imgui_EndPopup(void);

// ------------------------
// Prop label
// ------------------------ 

void imgui_labelPropBegin(const char *label, int id);

void imgui_labelPropEnd(void);

void imgui_labelPropReset(void);
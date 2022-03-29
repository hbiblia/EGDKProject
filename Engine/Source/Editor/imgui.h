#include <stdio.h>

// ------------------------
// Popup
// ------------------------
void imgui_OpenPopup(const char *id);
bool imgui_BeginPopup(const char* str_id);
bool imgui_BeginPopupModal(const char* str_id);
bool imgui_BeginPopupContextItem(const char* str_id,ImGuiPopupFlags popup_flags);
void imgui_EndPopup(void);

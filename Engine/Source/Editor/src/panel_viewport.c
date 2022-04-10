#include <stdio.h>

#define CIMGUI_IMPL
#include "ermine.h"
#include "ermine-flower.h"

#include "ermine-scene.h"
#include "ermine-util.h"

static ecamera default_cam;

// ---------------------------
// FUNCs
// ---------------------------

static void drawing_window(const ImDrawList *dl, const ImDrawCmd *cmd);
static void viewport_ui_toolbar(void);

// ------------------------
// Viewport-Init
// ------------------------

void panel_viewport_init(void)
{
    default_cam = ermine_camera_make();
}

// ------------------------
// Viewport-Renderer
// ------------------------

void panel_viewport_main(void)
{
    const char *title = STRDUPPF("Viewport - %s", ermine_scene_active_get_name());
    igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f, 0.0f});
    // igPushID_Str("Viewport");
    if (igBegin("Viewport", false, ImGuiWindowFlags_NoMove))
    {
        viewport_ui_toolbar();

        if (igBeginChild_Str("viewport_content", (ImVec2){0, 0}, false, 0))
        {
            ImDrawList *dl = igGetWindowDrawList();
            ImDrawList_AddCallback(dl, drawing_window, 0);
        }
        igEndChild();
    }
    igEnd();
    // igPopID();
    igPopStyleVar(1);
}

// ------------------------
// Viewport-Drawing-Render
// ------------------------

void drawing_window(const ImDrawList *dl, const ImDrawCmd *cmd)
{
    (void)dl;

    const int cx = (int)cmd->ClipRect.x;
    const int cy = (int)cmd->ClipRect.y;
    const int cw = (int)(cmd->ClipRect.z - cmd->ClipRect.x);
    const int ch = (int)(cmd->ClipRect.w - cmd->ClipRect.y);

    ermine_camera_set_viewport(&default_cam, cx, cy, cw, ch, true);
    ermine_begin_mode(default_cam);
    {
        flower_internal_system_run("EventSystemOnRender");
    }
    ermine_end_mode();
}

// ------------------------
// Viewport-Toolbar
// ------------------------

void viewport_ui_toolbar(void)
{
    if (igButton("Save", (ImVec2){0, 0}))
    {
        ermine_scene_save();
    }
    igSameLine(0.0f, 5.0f);
    if (igButton("Play", (ImVec2){0, 0}))
    {
    }
    igSameLine(0.0f, 5.0f);
    if (igButton("Stop", (ImVec2){0, 0}))
    {
    }
    igSameLine(0.0f, 5.0f);
    if (igButton("Build", (ImVec2){0, 0}))
    {
    }
}

#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <flower.h>

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
    default_cam = ecamera_make();
}

// ------------------------
// Viewport-Renderer
// ------------------------

void panel_viewport_main(void)
{
    igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f, 0.0f});
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

    erender_camera_set_viewport(&default_cam, cx, cy, cw, ch, true);
    ebegin_mode(default_cam);
    {
        flower_internal_system_run("EventSystemOnRender");
    }
    eend_mode();
}

// ------------------------
// Viewport-Toolbar
// ------------------------

void viewport_ui_toolbar(void)
{
    if (igButton("Save", (ImVec2){0, 0}))
    {
        eresource_scene_save();
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

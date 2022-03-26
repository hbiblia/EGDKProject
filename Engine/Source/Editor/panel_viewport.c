#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <flower.h>

void drawing_window(const ImDrawList *dl, const ImDrawCmd *cmd);

static ecamera default_cam;

void panel_viewport_init(void)
{
    default_cam = ecamera_make();
}

void panel_viewport_main(void)
{
    igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f,0.0f});
    if (igBegin("Viewport", false, ImGuiWindowFlags_NoMove))
    {
        ImDrawList *dl = igGetWindowDrawList();
        ImDrawList_AddCallback(dl, drawing_window, 0);
    }
    igEnd();
    igPopStyleVar(1);
}

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

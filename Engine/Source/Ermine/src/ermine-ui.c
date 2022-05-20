#include "ermine-ui.h"
#include "ermine-window.h"

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
// #include "sokol/sokol_glue.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

#define SOKOL_IMGUI_IMPL
#include "sokol/sokol_imgui.h"

void ermine_ui_init(int samples)
{
    printf("INFO: Init CImGui\n");

    simgui_setup(&(simgui_desc_t){
        .sample_count = sapp_sample_count()});

    ImGuiIO *io = igGetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigDockingWithShift = true;
}

void ermine_ui_frame(void)
{
    simgui_new_frame(&(simgui_frame_desc_t){
        .width = ermine_window_width(),
        .height = ermine_window_height(),
        .delta_time = ermine_window_delta(),
        .dpi_scale = ermine_window_dpi(),
    });
}

void ermine_ui_draw(void)
{
    simgui_render();
}

void ermine_ui_event(const void *ev)
{
    const sapp_event *event = (sapp_event*)ev;
    simgui_handle_event(event);
}

void ermine_ui_close(void)
{
    simgui_shutdown();
}
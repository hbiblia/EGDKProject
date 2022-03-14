
/*
 * Administramos la ventana o ventanas.
 *
 *
 */

#define SOKOL_IMPL
#define SOKOL_NO_ENTRY
#define SOKOL_GL_IMPL
#define CIMGUI_IMPL
#include "ermine.h"

// #define SOKOL_IMGUI_IMPL
#include "sokol/sokol_imgui.h"

static ewindow_desc wdefault;

static void init_default(void)
{
    sg_setup(&(sg_desc){
        .context = sapp_sgcontext()});

    sgl_setup(&(sgl_desc_t){0});

    simgui_setup(&(simgui_desc_t){ 0 });

    wdefault.pass_action = (sg_pass_action) {
        .colors[0] = { .action = SG_ACTION_CLEAR, .value = { 0.0f, 0.0f, 0.0f, 1.0 } }
    };

    if(wdefault.init_fn)wdefault.init_fn();
}

static void frame_default(void)
{
    simgui_new_frame(&(simgui_frame_desc_t){
        .width = ewindow_width(),
        .height = ewindow_height(),
        .delta_time = sapp_frame_duration(),
        .dpi_scale = sapp_dpi_scale()
    });

    if(wdefault.update_fn)wdefault.update_fn();

    sg_begin_default_pass(&wdefault.pass_action, ewindow_width(), ewindow_height());
    simgui_render();
    sg_end_pass();
    sg_commit();
}

static void event_default(const sapp_event* ev)
{
    simgui_handle_event(ev);
    if(wdefault.event_fn)wdefault.event_fn(ev);
}

static void shutdown_default(void)
{
    if(wdefault.shutdown_fn)wdefault.shutdown_fn();
    simgui_shutdown();
    sgl_shutdown();
    sg_shutdown();
}

void ewindow_init(ewindow_desc win)
{
    wdefault = win;

    sapp_run(&(sapp_desc){
        .window_title = win.title,
        .width = win.width,
        .height = win.height,
        .init_cb = init_default,
        .frame_cb = frame_default,
        .cleanup_cb = shutdown_default,
        .event_cb = event_default
    });
}

int ewindow_width(void)
{
    return sapp_width();
}

int ewindow_height(void)
{
    return sapp_height();
}

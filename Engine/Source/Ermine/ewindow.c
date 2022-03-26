
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
#include "flower.h"

#include "sokol/sokol_imgui.h"

static ewindow_desc wdefault;

static void init_default(void)
{
    sg_setup(&(sg_desc){
        .context = sapp_sgcontext()});

    sgl_setup(&(sgl_desc_t){0});

    simgui_setup(&(simgui_desc_t){
        .sample_count = sapp_sample_count()});

    wdefault.pass_action = (sg_pass_action){
        .colors[0] = {.action = SG_ACTION_CLEAR, .value = {0.0f, 0.0f, 0.0f, 1.0}}};

    ecs_flecs_init();
    eresource_init(wdefault.path_project);

    if (wdefault.init_fn)
        wdefault.init_fn();
}

static void frame_default(void)
{
    simgui_new_frame(&(simgui_frame_desc_t){
        .width = ewindow_width(),
        .height = ewindow_height(),
        .delta_time = sapp_frame_duration(),
        .dpi_scale = sapp_dpi_scale()});

    if (wdefault.update_fn)
        wdefault.update_fn();

    ecs_flecs_progress();

    sg_begin_default_pass(&wdefault.pass_action, ewindow_width(), ewindow_height());
    sgl_draw();
    simgui_render();
    sg_end_pass();
    sg_commit();

    input_pollinput();
}

static void event_default(const sapp_event *ev)
{
    simgui_handle_event(ev);

    if (ev->type == SAPP_EVENTTYPE_KEY_DOWN)
    {
        input_key_set_down(ev->key_code);
    }
    else if (ev->type == SAPP_EVENTTYPE_KEY_UP)
    {
        input_key_set_up(ev->key_code);
    }

    if (wdefault.event_fn)
        wdefault.event_fn(ev);
}

static void shutdown_default(void)
{
    if (wdefault.shutdown_fn)
        wdefault.shutdown_fn();

    ecs_flecs_close();
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
        .event_cb = event_default});
}

int ewindow_width(void)
{
    return sapp_width();
}

int ewindow_height(void)
{
    return sapp_height();
}

void ewindow_set_color(float r, float g, float b)
{
    wdefault.pass_action.colors[0].value = (sg_color){r, g, b, 1.0f};
}

ecolor ewindow_color(void)
{
    sg_color c = wdefault.pass_action.colors[0].value;
    return (ecolor){c.r, c.g, c.b, 1.0f};
}

void ewindow_set_title(const char *title)
{
    sapp_set_window_title(title);
}

void ewindow_close(void)
{
    sapp_quit();
}
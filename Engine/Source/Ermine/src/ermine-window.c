#include "ermine-window.h"
#include "ermine-ecs.h"
#include "ermine-gfx-renderer.h"
#include "ermine-resource.h"
#include "ermine-ui.h"

#include <time.h>

#define SOKOL_IMPL
#define SOKOL_NO_ENTRY
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_gl.h"

static bool bWindowInit = false;

static ermine_window_desc_t default_win = {0};

static void window__ini_sapp()
{
    sg_context_desc ctx = sapp_sgcontext();

    sg_setup(&(sg_desc){
        .context = ctx});

    sgl_setup(&(sgl_desc_t){0});

    ermine_ui_init(ctx.sample_count);

    ermine_renderer_init();

    time_t t;
    srand((unsigned)time(&t));

    if (default_win.fn_init)
        default_win.fn_init();
}
static void window__frame_sapp()
{
    float delta = sapp_frame_duration();

    ermine_renderer_begin();
    {
        if (default_win.fn_renderer)
            default_win.fn_renderer();

        ermine_ecs_progress();
    }
    ermine_renderer_end();
}
static void window__events_sapp(const sapp_event *event)
{
    ermine_ui_event(event);
}
static void window__shutdown_sapp()
{
    ermine_renderer_close();
    ermine_resource_close();
    printf("INFO: Close window\n");
}

void ermine_window_close(void)
{
    if (bWindowInit)
    {
        sapp_quit();
    }

    exit(-1);
}

void ermine_window_new(const char *title, int width, int height)
{
    default_win = (ermine_window_desc_t){
        .title = title,
        .width = width,
        .height = height,
    };
    bWindowInit = true;
}

void ermine_window_fn_init(void (*fn_init)(void))
{
    default_win.fn_init = fn_init;
}

void ermine_window_fn_renderer(void (*fn_renderer)(void))
{
    default_win.fn_renderer = fn_renderer;
}

void ermine_window_main(void)
{
    // Obtenemos los datos de config del proyecto
    JSON_Value *config = ermine_resource_get_object(RESOURCE_OPROJECT);
    if (config != NULL)
    {
        JSON_Object *oo = json_value_get_object(config);

        JSON_Object *win = json_object_get_object(oo, "window");

        ermine_window_new(json_object_get_string(win, "title"),
                          json_object_get_number(win, "width"),
                          json_object_get_number(win, "height"));
        json_object_clear(win);
        json_object_clear(oo);
    }

    //
    if (bWindowInit)
    {
        sapp_run(&(sapp_desc){
            .window_title = default_win.title,
            .width = default_win.width,
            .height = default_win.height,
            .init_cb = window__ini_sapp,
            .frame_cb = window__frame_sapp,
            .cleanup_cb = window__shutdown_sapp,
            .event_cb = window__events_sapp,
        });
    }
}

void ermine_window_set_title(const char *title)
{
    default_win.title = title;
    sapp_set_window_title(title);
}

void ermine_window_set_size(int width, int height)
{
    default_win.width = width;
    default_win.height = height;
}

void ermine_window_set_resize(bool enable)
{
    sapp_is_fullscreen();
}

const char *ermine_window_title(void)
{
    return default_win.title;
}

int ermine_window_width(void)
{
    default_win.width = sapp_width();
    return default_win.width;
}

int ermine_window_height(void)
{
    default_win.height = sapp_height();
    return default_win.height;
}

float ermine_window_delta(void)
{
    return sapp_frame_duration();
}

float ermine_window_dpi(void)
{
    return sapp_dpi_scale();
}

bool ermine_window_is_init(void)
{
    return bWindowInit;
}

ermine_window_desc_t ermine_window_get_default(void)
{
    return default_win;
}

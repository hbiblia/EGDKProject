#ifndef ERMINE_H
#define ERMINE_H
#include <stdio.h>
#include <stdlib.h>

#define ERMINE_VERSION  "1.0-dev"

#define EAPI

#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define EAPI __declspec(dllexport)
    #elif defined(USE_LIBTYPE_SHARED)
        #define EAPI __declspec(dllimport)
    #endif
#endif


// SOKOLs
#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_time.h"
#include "sokol/sokol_gl.h"

#if defined(CIMGUI_IMPL)
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"
#endif

// 
typedef struct ewindow_desc
{
    const char *title;
    int width;
    int height;
    void (*init_fn)();
    void (*update_fn)();
    void (*shutdown_fn)();
    void (*event_fn)(void*);
    sg_pass_action pass_action;
}ewindow_desc;

// EWINDOW

EAPI void ewindow_init(ewindow_desc win);
EAPI int ewindow_width(void);
EAPI int ewindow_height(void);

#endif // ERMINE_H+
#ifndef ERMINE_H
#define ERMINE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ERMINE_VERSION "1.0-dev"

#define EAPI
#define ermine_public

#if defined(_WIN32)
#if defined(BUILD_LIBTYPE_SHARED)
#define EAPI __declspec(dllexport)
#elif defined(USE_LIBTYPE_SHARED)
#define EAPI __declspec(dllimport)
#endif
#endif

#if defined(_WIN32)
#if defined(BUILD_LIBTYPE_SHARED)
#define ermine_public __declspec(dllexport)
#elif defined(USE_LIBTYPE_SHARED)
#define ermine_public __declspec(dllimport)
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

#include "ermine-input.h"
#include <glib.h>

#include "parson/parson.h"

enum
{
    ELOG_TRACE,
    ELOG_DEBUG,
    ELOG_INFO,
    ELOG_WARN,
    ELOG_ERROR,
    ELOG_FATAL
};

enum
{
    RESOURCE_PATH_PROJECT,
    RESOURCE_PATH,
    RESOURCE_PATH_ENGINE,
    RESOURCE_LAST
};

enum
{
    CAMERA_ORTHOGRAPHIC,
    CAMERA_PERSPECTIVE
};

#define VD(v, m, d) v == m ? d : v
#define COLORD(color) ecolor_empty(color) ? WHITE : color
#define ECOLOR_RGBA_T(r, g, b, a) (ecolor){(r) / 255.0f, (g) / 255.0f, (b) / 255.0f, (a) / 255.0f}

#define LIGHTGRAY  ECOLOR_RGBA_T(200, 200, 200, 255)   // Light Gray
#define GRAY       ECOLOR_RGBA_T(130, 130, 130, 255)   // Gray
#define DARKGRAY   ECOLOR_RGBA_T(80, 80, 80, 255)      // Dark Gray
#define YELLOW     ECOLOR_RGBA_T(253, 249, 0, 255)     // Yellow
#define GOLD       ECOLOR_RGBA_T(255, 203, 0, 255)     // Gold
#define ORANGE     ECOLOR_RGBA_T(255, 161, 0, 255)     // Orange
#define PINK       ECOLOR_RGBA_T(255, 109, 194, 255)   // Pink
#define RED        ECOLOR_RGBA_T(230, 41, 55, 255)     // Red
#define MAROON     ECOLOR_RGBA_T(190, 33, 55, 255)     // Maroon
#define GREEN      ECOLOR_RGBA_T(0, 228, 48, 255)      // Green
#define LIME       ECOLOR_RGBA_T(0, 158, 47, 255)      // Lime
#define DARKGREEN  ECOLOR_RGBA_T(0, 117, 44, 255)      // Dark Green
#define SKYBLUE    ECOLOR_RGBA_T(102, 191, 255, 255)   // Sky Blue
#define BLUE       ECOLOR_RGBA_T(0, 121, 241, 255)     // Blue
#define DARKBLUE   ECOLOR_RGBA_T(0, 82, 172, 255)      // Dark Blue
#define PURPLE     ECOLOR_RGBA_T(200, 122, 255, 255)   // Purple
#define VIOLET     ECOLOR_RGBA_T(135, 60, 190, 255)    // Violet
#define DARKPURPLE ECOLOR_RGBA_T(112, 31, 126, 255)    // Dark Purple
#define BEIGE      ECOLOR_RGBA_T(211, 176, 131, 255)   // Beige
#define BROWN      ECOLOR_RGBA_T(127, 106, 79, 255)    // Brown
#define DARKBROWN  ECOLOR_RGBA_T(76, 63, 47, 255)      // Dark Brown

#define WHITE      ECOLOR_RGBA_T(255, 255, 255, 255)   // White
#define BLACK      ECOLOR_RGBA_T(0, 0, 0, 255)         // Black
#define BLANK      ECOLOR_RGBA_T(0, 0, 0, 0)           // Blank (Transparent)
#define MAGENTA    ECOLOR_RGBA_T(255, 0, 255, 255)     // Magenta

typedef struct ecolor
{
    float r, g, b, a;
} ecolor;

typedef struct erect
{
    float x, y, width, height;
} erect;

typedef struct evect2
{
    float x, y;
} evect2;

typedef struct evect3
{
    float x, y, z;
} evect3;

typedef void (*efuntion)();

typedef struct etransform
{
    evect3 position;
    evect3 scale;
    evect3 rotation;
    evect3 localPosition;
    evect3 localRotation;
    evect3 localScale;
} etransform;

typedef struct erectangle_desc
{
    float width;
    float height;
    float size;
    ecolor color;
    etransform transform;
}eshape_desc;

typedef struct ecamera
{
    evect3 position;
    evect3 rotation;
    sgl_pipeline pip;
    int projection;
    float fovy;
    // viewport
    int viewport_w;
    int viewport_h;
    int viewport_x;
    int viewport_y;
    bool scissor;
}ecamera;

typedef struct etexture
{
    unsigned int id;
    int width;
    int height;
} etexture;

typedef struct etexture_desc
{
    etexture source;
    ecolor color;
    erect clip;
    bool flipx;
    bool flipy;
    etransform transform;
} etexture_desc;

typedef struct ewindow_desc
{
    const char *title;
    int width;
    int height;
    void (*init_fn)();
    void (*update_fn)();
    void (*before_update)();
    void (*shutdown_fn)();
    void (*event_fn)(void *);
    sg_pass_action pass_action;
    char *path_project;
} ewindow_desc;

// EUTILITY

EAPI unsigned char *eutil_loadfile_data(const char *filename, unsigned int *bytes);

EAPI void etracelog(int t, const char *text, ...);

const char *eutil_file_get_extension(const char *filename);

bool eutil_isfile_extension(const char *filename, const char *ext);

const char *eutil_file_get_name(const char *filepath);

char *eutil_path_normalize(const char *path);

int eutil_genrandom_number(int length);

#define PATH_BUILD(...) eutil_path_normalize(g_build_filename(__VA_ARGS__, NULL))

#define STRDUPPF g_strdup_printf

#define BASENAME g_path_get_basename 

// EWINDOW

EAPI void ewindow_init(ewindow_desc win);

EAPI int ewindow_width(void);

EAPI int ewindow_height(void);

EAPI void ewindow_set_color(float r, float g, float b);

EAPI ecolor ewindow_color(void);

EAPI void ewindow_set_title(const char *title);

EAPI void ewindow_close(void);

// ETEXTURE

EAPI void etexture_draw(etexture_desc t);

EAPI etexture etexture_load(const char *filename);

// ERENDER

EAPI void ebegin_mode(ecamera cam);

EAPI void eend_mode(void);

EAPI ecamera ecamera_make(void);

void erender_camera_set_viewport(ecamera *cam, int x, int y, int w, int h, bool scissor);

// ESHAPE

EAPI void eshape_triangle_draw(eshape_desc shape);

EAPI void eshape_rectangle_draw(eshape_desc shape);

// ECOLOR

EAPI bool ecolor_empty(ecolor color);

EAPI ecolor ecolor_new(float r, float g, float b, float a);

// EMATH
EAPI evect2 evect2_new(float x, float y);

EAPI evect3 evect3_new(float x, float y, float z);

#endif // ERMINE_H+
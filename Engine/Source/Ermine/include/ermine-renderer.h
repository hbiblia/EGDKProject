#ifndef ERMINE_RENDERER_H
#define ERMINE_RENDERER_H

#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gl.h"
#include "ermine-config.h"
#include "ermine.h"

#ifdef __cplusplus
extern "C"
{
#endif

    ermine_public void ermine_begin_mode(ecamera cam);

    ermine_public void ermine_end_mode(void);

    ermine_public ecamera ermine_camera_make(void);

    ermine_public void ermine_camera_set_viewport(ecamera *cam, int x, int y, int w, int h, bool scissor);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_RENDERER_H
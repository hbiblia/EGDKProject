#include "ermine-renderer.h"

void ermine_begin_mode(ecamera cam)
{
    int screenw = cam.viewport_w == 0 ? ewindow_width() : cam.viewport_w;
    int screenh = cam.viewport_h == 0 ? ewindow_height() : cam.viewport_h;
    int screenx = cam.viewport_x;
    int screeny = cam.viewport_y;

    float aspect = (float)screenw / (float)screenh;
    float scale = 700.0f;

    // Viewport scissor
    if (cam.scissor)
        sg_apply_scissor_rect(screenx, screeny, screenw, screenh, true);
    sgl_viewport(screenx, screeny, screenw, screenh, true);

    sgl_defaults();
    sgl_push_pipeline();
    sgl_load_pipeline(cam.pip);
    sgl_matrix_mode_projection();
    if (cam.projection == CAMERA_ORTHOGRAPHIC)
    {
        float ortho_size = (aspect * scale);
        sgl_ortho(-ortho_size, +ortho_size, -scale, +scale, -1.0f, +1.0f);
    }
    else
    {
        sgl_perspective(sgl_rad(cam.fovy), aspect, -0.1f, 1000.0f);
        sgl_matrix_mode_modelview();
    }
    sgl_push_matrix();
}

void ermine_end_mode(void)
{
    sgl_pop_matrix();
    sgl_pop_pipeline();
    sgl_draw();
}

ecamera ermine_camera_make(void)
{
    ecamera cam = {0};

    cam.pip = sgl_make_pipeline(&(sg_pipeline_desc){
        // .cull_mode = SG_CULLMODE_BACK,
        .depth = {
            .write_enabled = true,
            .compare = SG_COMPAREFUNC_LESS_EQUAL,
        },
        .colors[0] = {
            .blend = {
                .enabled = true,
                .src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA,
                .dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            },
        },
    });

    cam.projection = CAMERA_ORTHOGRAPHIC;
    cam.fovy = 45.0f;

    return cam;
}

void ermine_camera_set_viewport(ecamera *cam, int x, int y, int w, int h, bool scissor)
{
    cam->viewport_x = x;
    cam->viewport_y = y;
    cam->viewport_w = w;
    cam->viewport_h = h;
    cam->scissor = scissor;
}

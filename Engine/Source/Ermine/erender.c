#include "ermine.h"

/*
 * Renderizado base
 *
 *
 */

void ebegin_mode(ecamera cam)
{
    const float aspect = sapp_widthf() / sapp_heightf();
    float scale = 700.0f;

    sgl_viewport(0, 0, ewindow_width(), ewindow_height(), true);
    sgl_defaults();
    // sgl_load_default_pipeline();
    sgl_push_pipeline();
    sgl_load_pipeline(cam.pip);

    sgl_matrix_mode_projection();
    sgl_load_identity();
    sgl_ortho(-aspect * scale, +aspect * scale, -scale, +scale, -1.0f, +1.0f);
    // sgl_perspective(sgl_rad(45.0f), aspect, -0.1f, 1000.0f);
    // sgl_translate(cam.position.x, cam.position.y, -10);
    // sgl_matrix_mode_modelview();
    // sgl_push_matrix();
    // sgl_matrix_mode_texture();
}

void eend_mode(void)
{
    // sgl_draw();
    // sgl_pop_matrix();
    sgl_pop_pipeline();
    // sgl_load_identity();
}

ecamera ecamera_make(void)
{
    ecamera cam = {0};

    cam.pip = sgl_make_pipeline(&(sg_pipeline_desc){
        // .cull_mode = SG_CULLMODE_BACK,
        .depth = {
            .write_enabled = true,
            .compare = SG_COMPAREFUNC_LESS_EQUAL,
        },
    });

    return cam;
}

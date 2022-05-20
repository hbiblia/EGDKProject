#include "ermine-gfx-renderer.h"
#include "ermine-window.h"
#include "ermine-ui.h"
#include "ermine-ctexture.h"
#include "ermine-types.h"

// #define SOKOL_IMPL
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gl.h"

static sg_pass_action pass_action;
static sgl_pipeline pipeline_default;

static ecolor render_color;

void ermine_renderer_init(void)
{
    printf("INFO: Init Renderer\n");

    pass_action = (sg_pass_action){
        .colors[0] = {.action = SG_ACTION_CLEAR, .value = {0.0f, 0.0f, 0.0f, 1.0f}}};

    pipeline_default = sgl_make_pipeline(&(sg_pipeline_desc){
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
}

void ermine_renderer_begin(void)
{
    // Update color
    pass_action.colors[0].value.r = render_color.r;
    pass_action.colors[0].value.g = render_color.g;
    pass_action.colors[0].value.b = render_color.b;

    // pass
    ermine_ui_frame();
    sg_begin_default_pass(&pass_action, ermine_window_width(), ermine_window_height());
    // ermine_camera_manager_begin(1);
}

void ermine_renderer_end(void)
{
    // ermine_camera_manager_end();
    ermine_r_draw();
    ermine_ui_draw();
    sg_end_pass();
    sg_commit();
}

void ermine_renderer_close(void)
{
    sgl_shutdown();
    ermine_ui_close();
    sg_shutdown();
}

void ermine_renderer_set_color(ecolor background)
{
    render_color.r = background.r;
    render_color.g = background.g;
    render_color.b = background.b;
}

void ermine_r_push_matrix(void)
{
    sgl_push_matrix();
}

void ermine_r_pop_matrix(void)
{
    sgl_pop_matrix();
}

void ermine_r_pipeline_begin(void)
{
    sgl_push_pipeline();
    sgl_load_pipeline(pipeline_default);
}

void ermine_r_pipeline_end(void)
{
    sgl_pop_pipeline();
}

void ermine_r_draw(void)
{
    sgl_draw();
}

void ermine_ortho(float l, float r, float b, float t, float n, float f)
{
    sgl_ortho(l, r, b, t, n, f);
}

void ermine_r_scissor(int x, int y, int w, int h)
{
    sg_apply_scissor_rect(x, y, w, h, true);
}

void ermine_r_viewport(int x, int y, int w, int h)
{
    sgl_viewport(x, y, w, h, true);
}

void ermine_r_defaults(void)
{
    sgl_defaults();
}

void ermine_r_projection(void)
{
    sgl_matrix_mode_projection();
}

void ermine_r_begin_quads(void)
{
    sgl_begin_quads();
}

void ermine_r_end(void)
{
    sgl_end();
}

void ermine_r_v2f_c3f(float x, float y, ecolor color)
{
    sgl_v2f_c3f(x, y, color.r, color.g, color.b);
}

static int _transform_parent_size = 0;

void ermine_r_transform_make_begin(etransform transform)
{
    // aplicamos las transformaciones de los padres si tiene.
    etransform *t = transform.parent;
    while (1)
    {
        if (t == NULL)
            break;

        sgl_push_matrix();
        sgl_translate(t->position.x, t->position.y, 0.0f);
        sgl_scale(t->scale.x, t->scale.y, 1);
        sgl_rotate(sgl_rad(t->angle), 0.0f, 0.0f, 1.0f);
        sgl_translate(-(t->pivot.x * t->box.x), -(t->pivot.y * t->box.y), 0.0f);

        _transform_parent_size++;
        t = t->parent;
    }

    // aplicamos la transformacion de la entidad
    float px = transform.position.x;
    float py = transform.position.y;
    float sx = transform.scale.x;
    float sy = transform.scale.y;
    float angle = transform.angle;

    sgl_push_matrix();
    sgl_translate(px, py, 0.0f);
    sgl_scale(sx, sy, 1);
    sgl_rotate(sgl_rad(angle), 0.0f, 0.0f, 1.0f);
    sgl_translate(-(transform.pivot.x * transform.box.x), -(transform.pivot.y * transform.box.y), 0.0f);
}

void ermine_r_transform_make_end(etransform transform)
{
    sgl_pop_matrix();
    for (int i = 0; i < _transform_parent_size; i++)
    {
        sgl_pop_matrix();
    }
    _transform_parent_size = 0;
}

void ermine_r_shape_rectangle_draw(const eshape_desc_t *shape)
{
    // default rect
    float w = shape->width;
    float h = shape->height;
    ecolor color = shape->color;
    etransform t = shape->transform;

    ermine_r_transform_make_begin(t);
    {
        sgl_begin_quads();
        {
            ermine_r_v2f_c3f(-w, -h, color);
            ermine_r_v2f_c3f(w, -h, color);
            ermine_r_v2f_c3f(w, h, color);
            ermine_r_v2f_c3f(-w, h, color);
        }
        sgl_end();
    }
    ermine_r_transform_make_end(t);
}

void ermine_r_texture_draw(const etexture_desc_t *t)
{
    if (t->source.id > 0)
    {
        ecolor tint = COLORD(t->color);
        float width = (float)t->source.width;
        float height = (float)t->source.height;

        // FLIP
        width *= t->flipx ? -1 : 1;
        height *= t->flipy ? -1 : 1;

        // UV + CLIP
        float clip_width = t->clip.width == 0 ? width : t->clip.width;
        float clip_height = t->clip.height == 0 ? height : t->clip.height;

        evec2 uv0 = {t->clip.x / width, t->clip.y / t->clip.height};
        evec2 uv1 = {t->clip.x / width, (t->clip.y + height) / t->clip.height};
        evec2 uv2 = {(t->clip.x + width) / clip_width, (t->clip.y + height) / t->clip.height};
        evec2 uv3 = {(t->clip.x + width) / clip_width, t->clip.y / height};

        float w = clip_width;
        float h = clip_height;

        sgl_enable_texture();
        sgl_texture((sg_image){t->source.id});

        ermine_r_transform_make_begin(t->transform);
        {
            sgl_begin_quads();
            {
                sgl_c3f(tint.r, tint.g, tint.b);
                sgl_v2f_t2f(+w, +h, uv0.x, uv0.y);
                sgl_v2f_t2f(+w, -h, uv1.x, uv1.y);
                sgl_v2f_t2f(-w, -h, uv2.x, uv2.y);
                sgl_v2f_t2f(-w, +h, uv3.x, uv3.y);
            }
            sgl_end();
        }
        ermine_r_transform_make_end(t->transform);

        sgl_disable_texture();
    }
}
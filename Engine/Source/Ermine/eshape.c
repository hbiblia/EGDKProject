#include "ermine.h"

/*
 * Shapw basico
 *
 *
 */

void eshape_triangle_draw(eshape_desc shape)
{
    // default rect
    float size = shape.size;
    ecolor color = COLORD(shape.color);
    // transform
    float x = shape.transform.position.x;
    float y = shape.transform.position.y;
    float z = shape.transform.position.z;
    float rx = shape.transform.rotation.x;
    float ry = shape.transform.rotation.y;
    float rz = shape.transform.rotation.z;
    float sx = VD(shape.transform.scale.x, 0.0f, 1.0f);
    float sy = VD(shape.transform.scale.y, 0.0f, 1.0f);
    float sz = VD(shape.transform.scale.z, 0.0f, 1.0f);
    // transform origin
    float ox = 0.0f;
    float oy = 0.0f;

    sgl_push_matrix();
    {
        sgl_translate(x, y, z);
        sgl_scale(sx, sy, sz);
        sgl_rotate(sgl_rad(rx), 1.0f, 0.0f, 0.0f);
        sgl_rotate(sgl_rad(ry), 0.0f, 1.0f, 0.0f);
        sgl_rotate(sgl_rad(rz), 0.0f, 0.0f, 1.0f);
        sgl_translate(-(ox*size), -(oy*size), 0.0f);

        sgl_begin_triangles();
        {
            sgl_v2f_c3f(0.0f, size, color.r, color.g, color.b);
            sgl_v2f_c3f(-size, -size, color.r, color.g, color.b);
            sgl_v2f_c3f(size, -size, color.r, color.g, color.b);
        }
        sgl_end();
    }
    sgl_pop_matrix();
}

void eshape_rectangle_draw(eshape_desc shape)
{
    // default rect
    float w = shape.width;
    float h = shape.height;
    ecolor color = COLORD(shape.color);
    // transform
    float x = shape.transform.position.x;
    float y = shape.transform.position.y;
    float z = shape.transform.position.z;
    float rx = shape.transform.rotation.x;
    float ry = shape.transform.rotation.y;
    float rz = shape.transform.rotation.z;
    float sx = VD(shape.transform.scale.x, 0.0f, 1.0f);
    float sy = VD(shape.transform.scale.y, 0.0f, 1.0f);
    float sz = VD(shape.transform.scale.z, 0.0f, 1.0f);
    // transform origin
    float ox = 0.0f;
    float oy = 0.0f;

    sgl_push_matrix();
    {
        sgl_translate(x, y, z);
        sgl_scale(sx, sy, sz);
        sgl_rotate(sgl_rad(rx), 1.0f, 0.0f, 0.0f);
        sgl_rotate(sgl_rad(ry), 0.0f, 1.0f, 0.0f);
        sgl_rotate(sgl_rad(rz), 0.0f, 0.0f, 1.0f);
        sgl_translate(-(ox*w), -(oy*h), 0.0f);

        sgl_begin_quads();
        {
            sgl_v2f_c3f(-w, -h, color.r, color.g, color.b);
            sgl_v2f_c3f(w, -h, color.r, color.g, color.b);
            sgl_v2f_c3f(w, h, color.r, color.g, color.b);
            sgl_v2f_c3f(-w, h, color.r, color.g, color.b);
        }
        sgl_end();
    }
    sgl_pop_matrix();
}

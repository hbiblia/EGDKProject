#pragma once

#ifndef ERMINE_RENDERER_H
#define ERMINE_RENDERER_H
#include <stdio.h>
#include "ermine-ccolor.h"
#include "ermine-ctransform.h"

typedef struct erectangle_desc
{
    float width;
    float height;
    ecolor color;
    etransform transform;
} eshape_desc_t;

void ermine_renderer_init(void);

void ermine_renderer_begin(void);
void ermine_renderer_end(void);

void ermine_renderer_close(void);
void ermine_renderer_set_color(ecolor background);

void ermine_r_push_matrix(void);
void ermine_r_pop_matrix(void);

void ermine_r_pipeline_begin(void);
void ermine_r_pipeline_end(void);

void ermine_r_defaults(void);
void ermine_r_draw(void);

void ermine_ortho(float l, float r, float b, float t, float n, float f);

void ermine_r_scissor(int x, int y, int w, int h);
void ermine_r_viewport(int x, int y, int w, int h);
void ermine_r_projection(void);

void ermine_r_begin_quads(void);
void ermine_r_end(void);
void ermine_r_v2f_c3f(float x, float y, ecolor color);

void ermine_r_shape_rectangle_draw(const eshape_desc_t *shape);
#endif // ERMINE_RENDERER_H
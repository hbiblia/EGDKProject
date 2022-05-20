#ifndef ERMINE_COMPONENT_SHAPES_H
#define ERMINE_COMPONENT_SHAPES_H
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine.h"
#include "ermine-ecs.h"
#include "ermine-ccolor.h"
#include "ermine-crenderer.h"

typedef struct {
    ecs_f32_t width;
    ecs_f32_t height;
    ecolor color;
    // renderer component required
    erenderer renderer;
}eshaperect;

ermine_private void ComponentBaseShapesImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_COMPONENT_SHAPES_H

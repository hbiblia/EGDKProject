#ifndef ERMINE_COMPONENT_TRANSFORM_H
#define ERMINE_COMPONENT_TRANSFORM_H
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine.h"
#include "ermine-ecs.h"
#include "ermine-cmath.h"

typedef struct etransform {
    evec2 position;
    evec2 scale;
    float angle;
    evec2 pivot;

    // ---------------
    // boundingBox
    // ---------------
    evec4 box;

    // ---------------
    // parent transform
    // ---------------
    struct etransform *parent;
}etransform;

ermine_private void ComponentBaseTransformImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_COMPONENT_TRANSFORM_H

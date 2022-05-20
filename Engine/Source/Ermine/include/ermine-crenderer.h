#ifndef ERMINE_COMPONENT_RENDERER_H
#define ERMINE_COMPONENT_RENDERER_H
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine.h"
#include "ermine-ecs.h"
#include "ermine-cmath.h"

typedef struct {
    int sortingLayerName ;
    int sortingOrder;
}erenderer;

int erenderer_order(ecs_entity_t entity_a, const void *component_1, ecs_entity_t entity_b, const void *component_2);

ermine_private void ComponentBaseRendererImport(ecs_world_t *world);
                       
#ifdef __cplusplus
}
#endif

#endif // ERMINE_COMPONENT_RENDERER_H

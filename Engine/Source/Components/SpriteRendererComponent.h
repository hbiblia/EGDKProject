#ifndef COMPONENT_SPRITERENDERER_H_
#define COMPONENT_SPRITERENDERER_H_

#include <ermine.h>
#include <flecs/flecs.h>
#include "ermine-flower.h"

ECS_STRUCT(SpriteRendererComponent, {
    char *key;
    CColor color;
    bool flipX;
    bool flipY;
    int8_t sortingOrder;
});

EAPI void SpriteRendererComponentImport(ecs_world_t *world);

#endif // COMPONENT_SPRITE_RENDERER_H_
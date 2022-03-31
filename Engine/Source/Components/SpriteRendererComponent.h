#ifndef COMPONENT_SPRITE_RENDERER_H_
#define COMPONENT_SPRITE_RENDERER_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "flower.h"

typedef struct {
    char *key;
    CColor color;
    bool flipX;
    bool flipY;
    uint8_t sortingOrder;
}SpriteRendererComponent;

EAPI void ComponentSpriteRendererImport(ecs_world_t *world);

#endif // COMPONENT_SPRITE_RENDERER_H_

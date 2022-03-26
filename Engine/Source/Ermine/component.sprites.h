#ifndef COMPONENT_SPRITES_H_
#define COMPONENT_SPRITES_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "flower.h"

typedef struct {
    char *key;
    CColor color;
    bool flipX;
    bool flipY;
}SpriteRendererComponent;

EAPI void ComponentSpritesImport(ecs_world_t *world);

#endif // COMPONENT_SPRITES_H_

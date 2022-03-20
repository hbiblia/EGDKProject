#ifndef COMPONENT_SPRITES_H_
#define COMPONENT_SPRITES_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "eactor.h"

typedef struct {
    char *key;
}EcsSprites;

EAPI void ComponentSpritesImport(ecs_world_t *world);

#endif // COMPONENT_SPRITES_H_

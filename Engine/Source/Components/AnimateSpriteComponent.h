#ifndef COMPONENT_ANIMATESPRITES_H_
#define COMPONENT_ANIMATESPRITES_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "flower.h"

typedef struct
{
    char *name;
    bool loop;
    int frames;
} AnimateAnimationDataComponent;

typedef struct
{
    int count;
    AnimateAnimationDataComponent animations;
} AnimateSpriteComponent;

EAPI void ComponentAnimateSpriteImport(ecs_world_t *world);

#endif // COMPONENT_ANIMATESPRITES_H_

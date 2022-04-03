#ifndef COMPONENT_ANIMATESPRITES_H_
#define COMPONENT_ANIMATESPRITES_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"

ECS_STRUCT(AnimateSpriteComponent,{
    int8_t count;
});

EAPI void AnimateSpriteComponentImport(ecs_world_t *world);

#endif // COMPONENT_ANIMATESPRITES_H_

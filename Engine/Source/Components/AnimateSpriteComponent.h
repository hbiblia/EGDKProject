#ifndef COMPONENT_ANIMATESPRITES_H_
#define COMPONENT_ANIMATESPRITES_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"

ECS_STRUCT(CAnimation, {
    char *slot;
    int8_t startFrame;
    int8_t endFrame;
    float speed;
    bool loop;
});

ECS_STRUCT(AnimateSpriteComponent,{
    CAnimation animation[5];
});

EAPI void AnimateSpriteComponentImport(ecs_world_t *world);

#endif // COMPONENT_ANIMATESPRITES_H_

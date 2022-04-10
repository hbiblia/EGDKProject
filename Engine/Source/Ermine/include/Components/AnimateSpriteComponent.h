#ifndef COMPONENT_ANIMATESPRITES_H_
#define COMPONENT_ANIMATESPRITES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"
#include "ermine-config.h"

#undef ECS_META_IMPL
#ifndef AnimateSpriteComponent_EXPORTS
#define ECS_META_IMPL EXTERN // Ensure meta symbols are only defined once
#endif

ECS_STRUCT(CAnimation, {
    char *slot;
    int8_t startFrame;
    int8_t endFrame;
    float speed;
    bool loop;
});

ECS_STRUCT(AnimateSpriteComponent,{
    CAnimation animation[2];
});

ermine_public void AnimateSpriteComponentImport(ecs_world_t *world);


#ifdef __cplusplus
}
#endif

#endif // COMPONENT_ANIMATESPRITES_H_

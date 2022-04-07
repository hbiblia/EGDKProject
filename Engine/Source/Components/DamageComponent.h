#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

#include <ermine.h>
#include "ermine-flower.h"

#undef ECS_META_IMPL
#ifndef DamageComponent_EXPORTS
#define ECS_META_IMPL EXTERN // Ensure meta symbols are only defined once
#endif

ECS_STRUCT(DamageComponent, {
    CVec3 total[2];
    int32_t TotalDamage[2];
    float DamageTimeInSeconds;
    float DamagePerSecond;
});

void DamageComponentInit(ecs_world_t *world);

#endif // DAMAGE_COMPONENT_H

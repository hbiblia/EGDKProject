#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <ermine.h>
#include "ermine-flower.h"
#include "ermine-config.h"

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

ermine_public void DamageComponentInit(ecs_world_t *world);


#ifdef __cplusplus
}
#endif

#endif // DAMAGE_COMPONENT_H

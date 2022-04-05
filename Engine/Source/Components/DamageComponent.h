#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

#include <ermine.h>
#include "ermine-flower.h"

ECS_STRUCT(DamageComponent, {
    int8_t TotalDamage[2];
    float DamageTimeInSeconds;
    float DamagePerSecond;
});

void DamageComponentInit(ecs_world_t *world);

#endif // DAMAGE_COMPONENT_H

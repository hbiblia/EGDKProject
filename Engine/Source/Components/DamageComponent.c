#define ECS_META_IMPLEMENT
#include "DamageComponent.h"

void DamageComponentInit(ecs_world_t *world)
{
    FLOWER_COMPONENT_INIT(DamageComponent);
}

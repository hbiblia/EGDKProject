#define InfoComponent_EXPORTS
#include "Components/InfoComponent.h"

void ComponentInfoImport(ecs_world_t *world)
{
    ECS_META_COMPONENT(world, InfoComponent);
}

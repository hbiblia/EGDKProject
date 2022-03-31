
#include "InfoComponent.h"


static void system__update_fn(ecs_iter_t *it)
{
    InfoComponent *info = ecs_term_w_size(it, sizeof(InfoComponent), 1);

    for (int i = 0; i < it->count; i++)
    {
        // printf("Entity transform\n");
    }
}

void ComponentInfoImport(ecs_world_t *world)
{
    COMPONENT_INIT(InfoComponent);

    // ---------------------
    // SYSTEM COMPONENTE
    // ---------------------

    ECS_SYSTEM(world, system__update_fn, EcsOnUpdate, InfoComponent);
}

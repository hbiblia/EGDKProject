#define DamageComponent_EXPORTS
#include "Components/DamageComponent.h"

static void system__init_fn(ecs_iter_t *it)
{
    DamageComponent *damage = ecs_term_w_size(it, sizeof(DamageComponent), 1);

    for (int i = 0; i < it->count; i++)
    {
    }
}

void DamageComponentInit(ecs_world_t *world)
{
    FLOWER_COMPONENT_INIT(world, DamageComponent);

    // ecs_observer_init(world, &(ecs_observer_desc_t){
    //     .filter.terms = {{.id = ecs_id(DamageComponent)}},
    //     .events = {EcsOnAdd},
    //     .callback = system__init_fn,
    // });
}

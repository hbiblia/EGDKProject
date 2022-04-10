// #include "Components/SpriteRendererComponent.h"

#define AnimateSpriteComponent_EXPORTS
#include "Components/AnimateSpriteComponent.h"

static void system__init_fn(ecs_iter_t *it)
{
    // AnimateSpriteComponent *animate = ecs_term_w_size(it, sizeof(AnimateSpriteComponent), 1);
    // for (int i = 0; i < it->count; i++)
    // {
    // }
}

static void system__update_fn(ecs_iter_t *it)
{
    // AnimateSpriteComponent *animate = ecs_term_w_size(it, sizeof(AnimateSpriteComponent), 1);
    // SpriteRendererComponent *sprite = ecs_term_w_size(it, sizeof(SpriteRendererComponent), 2);
    // for (int i = 0; i < it->count; i++)
    // {
    // }
}

void AnimateSpriteComponentImport(ecs_world_t *world)
{
    // COMPONENTE INIT
    // ---------------------
    // ECS_META_COMPONENT(world, CAnimation);
    // FLOWER_COMPONENT_INIT(world, AnimateSpriteComponent);

    // SYSTEM & OBSERVER
    // ---------------------
    // ecs_observer_init(world, &(ecs_observer_desc_t){
    //     .filter.terms = {{.id = ecs_id(AnimateSpriteComponent)}},
    //     .events = {EcsOnSet, EcsOnAdd},
    //     .callback = system__init_fn,
    // });

    // ecs_system_init(world, &(ecs_system_desc_t){
    //     .entity = {.add = {EcsOnUpdate}},
    //     .query = {
    //         .filter.terms = {
    //             {.id = ecs_id(AnimateSpriteComponent)},
    //             {.id = flower_lookup("SpriteRendererComponent"), .inout = EcsIn},
    //         },
    //     },
    //    .callback = system__update_fn,
    // });
}

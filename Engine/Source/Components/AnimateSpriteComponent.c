// #include "SpriteRendererComponent.h"

#define ECS_META_IMPLEMENT
#include "AnimateSpriteComponent.h"

static void system__init_fn(ecs_iter_t *it)
{
    AnimateSpriteComponent *animate = ecs_term_w_size(it, sizeof(AnimateSpriteComponent), 1);

    for (int i = 0; i < it->count; i++)
    {
    }
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
    FLOWER_COMPONENT_INIT(AnimateSpriteComponent);

    // ecs_entity_t IdAnimateAnimationDataComponent = ecs_component_init(world, &(ecs_component_desc_t){
    //     .entity.name = "AnimateAnimationDataComponent",
    //     .size = sizeof(AnimateAnimationDataComponent),
    //     .alignment = ECS_ALIGNOF(AnimateAnimationDataComponent),
    // });

    // ecs_struct_init(world, &(ecs_struct_desc_t){
    //     .entity.entity = IdAnimateAnimationDataComponent,
    //        .members = {
    //             { .name = "name", .type = ecs_id(ecs_string_t) },
    //             { .name = "loop", .type = ecs_id(ecs_bool_t) },
    //             { .name = "frames", .type = ecs_id(ecs_i8_t) },
    //         },
    // });

    // ecs_entity_t IdAnimateSpriteComponent = ecs_component_init(world, &(ecs_component_desc_t){
    //     .entity.name = "AnimateSpriteComponent",
    //     .size = sizeof(AnimateSpriteComponent),
    //     .alignment = ECS_ALIGNOF(AnimateSpriteComponent),
    // });

    // ecs_struct_init(world, &(ecs_struct_desc_t){
    //     .entity.entity = IdAnimateSpriteComponent,
    //        .members = {
    //             { .name = "count", .type = ecs_id(ecs_i8_t) },
    //             { .name = "animations", .type = IdAnimateAnimationDataComponent },
    //         },
    // });

    // SYSTEM & OBSERVER
    // ---------------------
    ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{.id = ecs_id(AnimateSpriteComponent)}},
        .events = {EcsOnSet, EcsOnAdd},
        .callback = system__init_fn,
    });

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = {.add = {EcsOnUpdate}},
        .query = {
            .filter.terms = {
                {.id = ecs_id(AnimateSpriteComponent)},
                {.id = flower_lookup("SpriteRendererComponent"), .inout = EcsIn},
            },
        },
       .callback = system__update_fn,
    });
}

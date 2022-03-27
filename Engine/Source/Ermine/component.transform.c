
#include "component.transform.h"

void system__update_fn(ecs_iter_t *it)
{
    TransformComponent *transform = ecs_term_w_size(it, sizeof(TransformComponent), 1);

    for (int i = 0; i < it->count; i++)
    {
        // printf("Entity transform\n");
    }
}

void ComponentTransformImport(ecs_world_t *world)
{
    // COMPONENTE POSITION
    // ---------------------
    ecs_entity_t IdCPosition = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CPosition",
        .size = sizeof(CPosition),
        .alignment = ECS_ALIGNOF(CPosition),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCPosition,
        .members = {
            { .name = "position", .type = actor_get_lookup("CVec3") },
        },
    });

    // COMPONENTE SCALE
    // ---------------------
    ecs_entity_t IdCScale = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CScale",
        .size = sizeof(CScale),
        .alignment = ECS_ALIGNOF(CScale),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCScale,
        .members = {
            { .name = "scale", .type = actor_get_lookup("CVec3") },
        },
    });

    // COMPONENTE ROTATION
    // ---------------------
    ecs_entity_t IdCRotation = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CRotation",
        .size = sizeof(CRotation),
        .alignment = ECS_ALIGNOF(CRotation),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCRotation,
        .members = {
            { .name = "rotation", .type = actor_get_lookup("CVec3") },
        },
    });

    // COMPONENTE TRANSFORM
    // ---------------------
    ecs_entity_t IdTransformComponent = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "TransformComponent",
        .size = sizeof(TransformComponent),
        .alignment = ECS_ALIGNOF(TransformComponent),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdTransformComponent,
        .members = {
            { .name = "position", .type = actor_get_lookup("CVec3") },
            { .name = "scale", .type = actor_get_lookup("CVec3") },
            { .name = "rotation", .type = actor_get_lookup("CVec3") },
            { .name = "origin", .type = actor_get_lookup("CVec2") },
        },
    });


    // SYSTEM COMPONENTE
    // ---------------------
    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = {.add = {EcsOnUpdate}},
        .query.filter.terms = {
            {.id = actor_get_lookup("TransformComponent")},
        },
       .callback = system__update_fn,
    });
}

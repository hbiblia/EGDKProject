
#include "component.transform.h"

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
    ecs_entity_t IdCTransform = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CTransform",
        .size = sizeof(CTransform),
        .alignment = ECS_ALIGNOF(CTransform),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCTransform,
        .members = {
            { .name = "position", .type = actor_get_lookup("CVec3") },
            { .name = "scale", .type = actor_get_lookup("CVec3") },
            { .name = "rotation", .type = actor_get_lookup("CVec3") },
            { .name = "origin", .type = actor_get_lookup("CVec2") },
        },
    });
}

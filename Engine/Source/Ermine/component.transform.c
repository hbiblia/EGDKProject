
#include "component.transform.h"

void ComponentTransformImport(ecs_world_t *world)
{
    // COMPONENTE POSITION
    // ---------------------
    ecs_entity_t IdEscPosition = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsPosition",
        .size = sizeof(EcsPosition),
        .alignment = ECS_ALIGNOF(EcsPosition),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEscPosition,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
            { .name = "z", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_component("EcsPosition", IdEscPosition);

    // COMPONENTE SCALE
    // ---------------------
    ecs_entity_t IdEscScale = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsScale",
        .size = sizeof(EcsScale),
        .alignment = ECS_ALIGNOF(EcsScale),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEscScale,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
            { .name = "z", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_component("EcsScale", IdEscScale);

    // COMPONENTE ROTATION
    // ---------------------
    ecs_entity_t IdEscRotation = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsRotation",
        .size = sizeof(EcsRotation),
        .alignment = ECS_ALIGNOF(EcsRotation),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEscRotation,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
            { .name = "z", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_component("EcsRotation", IdEscRotation);

    // COMPONENTE TRANSFORM
    // ---------------------
    ecs_entity_t IdEscTransform = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsTransform",
        .size = sizeof(EcsTransform),
        .alignment = ECS_ALIGNOF(EcsTransform),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEscTransform,
        .members = {
            { .name = "position", .type = IdEscPosition },
            { .name = "scale", .type = IdEscScale },
            { .name = "rotation", .type = IdEscRotation },
        },
    });

    ecs_component("EcsTransform", IdEscTransform);
}

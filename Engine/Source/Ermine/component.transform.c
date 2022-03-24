
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
            { .name = "position", .type = ECS_COMPONENT_ID("EcsVect3") },
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
            { .name = "scale", .type = ECS_COMPONENT_ID("EcsVect3") },
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
            { .name = "rotation", .type = ECS_COMPONENT_ID("EcsVect3") },
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
            { .name = "position", .type = ECS_COMPONENT_ID("EcsVect3") },
            { .name = "scale", .type = ECS_COMPONENT_ID("EcsVect3") },
            { .name = "rotation", .type = ECS_COMPONENT_ID("EcsVect3") },
            { .name = "origin", .type = ECS_COMPONENT_ID("EcsVect3") },
        },
    });

    ecs_component("EcsTransform", IdEscTransform);
}

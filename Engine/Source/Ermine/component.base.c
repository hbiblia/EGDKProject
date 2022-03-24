
#include "component.base.h"

void ComponentBaseImport(ecs_world_t *world)
{
    // COMPONENTE BASE
    // ---------------------


    // COLOR
    // ---------------------
    ecs_entity_t IdEscColor = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsColor",
        .size = sizeof(EcsColor),
        .alignment = ECS_ALIGNOF(EcsColor),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEscColor,
        .members = {
            { .name = "r", .type = ecs_id(ecs_f32_t) },
            { .name = "g", .type = ecs_id(ecs_f32_t) },
            { .name = "b", .type = ecs_id(ecs_f32_t) },
            { .name = "a", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_component("EcsColor", IdEscColor);

    // VECTORs
    // ---------------------
    ecs_entity_t IdEcsVect2 = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsVect2",
        .size = sizeof(EcsVect2),
        .alignment = ECS_ALIGNOF(EcsVect2),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEcsVect2,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_component("EcsVect2", IdEcsVect2);

    ecs_entity_t IdEcsVect3 = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsVect3",
        .size = sizeof(EcsVect3),
        .alignment = ECS_ALIGNOF(EcsVect3),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEcsVect3,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
            { .name = "z", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_component("EcsVect3", IdEcsVect3);

    // RECTANGLE
    // ---------------------
    ecs_entity_t IdEcsRect = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsRect",
        .size = sizeof(EcsRect),
        .alignment = ECS_ALIGNOF(EcsRect),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEcsRect,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_component("EcsRect", IdEcsRect);
}

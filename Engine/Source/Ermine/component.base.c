
#include "component.base.h"

void ComponentBaseImport(ecs_world_t *world)
{
    // COMPONENTE BASE
    // ---------------------


    // COLOR
    // ---------------------
    ecs_entity_t IdCColor = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CColor",
        .size = sizeof(CColor),
        .alignment = ECS_ALIGNOF(CColor),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCColor,
        .members = {
            { .name = "r", .type = ecs_id(ecs_f32_t) },
            { .name = "g", .type = ecs_id(ecs_f32_t) },
            { .name = "b", .type = ecs_id(ecs_f32_t) },
            { .name = "a", .type = ecs_id(ecs_f32_t) },
        },
    });

    // VECTORs
    // ---------------------
    ecs_entity_t IdCVec2 = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CVec2",
        .size = sizeof(CVec2),
        .alignment = ECS_ALIGNOF(CVec2),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCVec2,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
        },
    });

    ecs_entity_t IdCVec3 = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CVec3",
        .size = sizeof(CVec3),
        .alignment = ECS_ALIGNOF(CVec3),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCVec3,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
            { .name = "z", .type = ecs_id(ecs_f32_t) },
        },
    });

    // RECTANGLE
    // ---------------------
    ecs_entity_t IdCRect = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "CRect",
        .size = sizeof(CRect),
        .alignment = ECS_ALIGNOF(CRect),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdCRect,
        .members = {
            { .name = "x", .type = ecs_id(ecs_f32_t) },
            { .name = "y", .type = ecs_id(ecs_f32_t) },
        },
    });
}

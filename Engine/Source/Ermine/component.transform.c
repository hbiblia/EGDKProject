
#include "component.transform.h"


static void system__update_fn(ecs_iter_t *it)
{
    TransformComponent *transform = ecs_term_w_size(it, sizeof(TransformComponent), 1);
    TransformComponent *transformParent = ecs_term_w_size(it, sizeof(TransformComponent), 2);

    for (int i = 0; i < it->count; i++)
    {
        // printf("Parent: X:%f\n", transformParent[i].position.x);
        // printf("Child: X:%f\n", transform[i].position.x);


    }
}

void ComponentTransformImport(ecs_world_t *world)
{
    // ---------------------
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
            { .name = "position", .type = flower_lookup("CVec3") },
        },
    });

    // ---------------------
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
            { .name = "scale", .type = flower_lookup("CVec3") },
        },
    });

    // ---------------------
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
            { .name = "rotation", .type = flower_lookup("CVec3") },
        },
    });

    // ---------------------
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
            { .name = "position", .type = flower_lookup("CVec3") },
            { .name = "scale", .type = flower_lookup("CVec3") },
            { .name = "rotation", .type = flower_lookup("CVec3") },
        },
    });


    // ---------------------
    // SYSTEM COMPONENTE
    // ---------------------
    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = {.add = {EcsOnUpdate}},
        .query = {
            .filter.terms = {
                {.id = flower_lookup("TransformComponent")},
                {.id = flower_lookup("TransformComponent"), .subj.set = {.mask = EcsParent | EcsCascade}, .inout = EcsIn},
            },
        },
       .callback = system__update_fn,
    });
}

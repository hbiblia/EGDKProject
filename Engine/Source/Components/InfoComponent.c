
#define ECS_META_IMPLEMENT
#include "InfoComponent.h"

static void system__update_fn(ecs_iter_t *it)
{
    InfoComponent *info = ecs_term_w_size(it, sizeof(InfoComponent), 1);

    for (int i = 0; i < it->count; i++)
    {
        // printf("Entity transform\n");
    }
}

void ComponentInfoImport(ecs_world_t *world)
{
    // ---------------------
    // COMPONENTE POSITION
    // ---------------------
    // ecs_entity_t IdCInfo = ecs_component_init(world, &(ecs_component_desc_t){
    //     .entity.name = "InfoComponent",
    //     .size = sizeof(InfoComponent),
    //     .alignment = ECS_ALIGNOF(InfoComponent),
    // });

    // ecs_struct_init(world, &(ecs_struct_desc_t){
    //     .entity.entity = IdCInfo,
    //     .members = {
    //         { .name = "name", .type = ecs_id(ecs_string_t) },
    //     },
    // });

    FLOWER_COMPONENT_INIT(InfoComponent);


    // ---------------------
    // SYSTEM COMPONENTE
    // ---------------------
    // ecs_system_init(world, &(ecs_system_desc_t){
    //     .entity = {.add = {EcsOnUpdate}},
    //     .query = {
    //         .filter.terms = {
    //             {.id = IdCInfo},
    //         },
    //     },
    //    .callback = system__update_fn,
    // });
}

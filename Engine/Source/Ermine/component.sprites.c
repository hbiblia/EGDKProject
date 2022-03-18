
#include "component.sprites.h"

void system__init_fn(ecs_iter_t *it)
{
    EcsSprites *sprite = ecs_term_w_size(it, sizeof(EcsSprites), 1);

    for (int i = 0; i < it->count; i ++) {
        // source = etexture_load(sprite[i].path);
    }
}

void system__render_fn(ecs_iter_t *it)
{
    EcsSprites *sprite = ecs_term_w_size(it, sizeof(EcsSprites), 1);

    for (int i = 0; i < it->count; i ++) {
        etexture_draw((etexture_desc){
            .source = eresource_get_texture(sprite[i].key),
        });
    }
}

void ComponentSpritesImport(ecs_world_t *world)
{
    // COMPONENTE SPRITES
    // ---------------------
    ecs_entity_t IdEscSprites = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "EcsSprites",
        .size = sizeof(EcsSprites),
        .alignment = ECS_ALIGNOF(EcsSprites),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdEscSprites,
        .members = {
            { .name = "key", .type = ecs_id(ecs_string_t) },
        },
    });

    component_custom_register_global("EcsSprites", IdEscSprites);

    // SYSTEM & OBSERVER COMPONENTE SPRITES
    // ---------------------
    // ecs_observer_init(world, &(ecs_observer_desc_t){
    //     .filter.terms = {{.id = IdEscSprites}},
    //     .events = {EcsOnSet},
    //     .callback = system__init_fn
    // });

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = {.add = {EcsOnStore} },
        .query.filter.terms = {{.id = IdEscSprites}},
        .callback = system__render_fn
    });
}

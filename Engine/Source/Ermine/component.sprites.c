
#include "component.sprites.h"
#include "component.transform.h"
#include <glib.h>

void system__init_fn(ecs_iter_t *it)
{
    CSprites *sprite = ecs_term_w_size(it, sizeof(CSprites), 1);

    for (int i = 0; i < it->count; i++)
    {
        sprite[i].key = sprite[i].key == NULL ? "" : sprite[i].key;
        sprite[i].color = ecolor_empty(sprite[i].color) ? WHITE : sprite[i].color;
    }
}

void system__render_fn(ecs_iter_t *it)
{
    CSprites *sprite = ecs_term_w_size(it, sizeof(CSprites), 1);
    CPosition *position = ecs_term_w_size(it, sizeof(CPosition), 2);
    CScale *scale = ecs_term_w_size(it, sizeof(CScale), 3);
    CRotation *rotation = ecs_term_w_size(it, sizeof(CRotation), 4);

    for (int i = 0; i < it->count; i++)
    {
        // Si el key esta en blanco no mostramos continuamos...
        if(strlen(sprite[i].key)==0)continue;

        etexture_draw((etexture_desc){
            .source = eresource_get_texture(sprite[i].key),
            .color = sprite[i].color,
            .flipx = sprite[i].flipX,
            .flipy = sprite[i].flipY,
            .transform = {
                .position = {position[i].x, position[i].y, position[i].z},
                .scale = {scale[i].x, scale[i].y, scale[i].z},
                .rotation = {rotation[i].x, rotation[i].y, rotation[i].z},
            },
        });
    }
}

void ComponentSpritesImport(ecs_world_t *world)
{
    // COMPONENTE SPRITES
    // ---------------------
    ecs_entity_t IdCSprites = ecs_component_init(world, &(ecs_component_desc_t){
                                                            .entity.name = "CSprites",
                                                            .size = sizeof(CSprites),
                                                            .alignment = ECS_ALIGNOF(CSprites),
                                                        });

    ecs_struct_init(world, &(ecs_struct_desc_t){
                               .entity.entity = IdCSprites,
                               .members = {
                                   {.name = "key", .type = ecs_id(ecs_string_t)},
                                   {.name = "color", .type = actor_get_lookup("CColor")},
                                   {.name = "flipX", .type = ecs_id(ecs_bool_t)},
                                   {.name = "flipY", .type = ecs_id(ecs_bool_t)},
                               },
                           });

    // SYSTEM & OBSERVER COMPONENTE SPRITES
    // ---------------------
    ecs_observer_init(world, &(ecs_observer_desc_t){
                                 .filter.terms = {{.id = IdCSprites}},
                                 .events = {EcsOnSet,EcsOnAdd},
                                 .callback = system__init_fn});

    ECS_TAG(world, EventSystemOnRender);

    ecs_system_init(world, &(ecs_system_desc_t){
                               .entity = {.name = "EventSystemOnRender", .add = {EventSystemOnRender}},
                               .query.filter.terms = {
                                   {.id = IdCSprites, .inout = EcsIn},
                                   {.id = actor_get_lookup("CPosition")},
                                   {.id = actor_get_lookup("CScale")},
                                   {.id = actor_get_lookup("CRotation")},
                               },
                               .callback = system__render_fn});
}

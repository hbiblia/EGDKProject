
#include "component.sprites.h"
#include "component.transform.h"
#include <glib.h>

static int sprites_sortingOrder(ecs_entity_t e1, const SpriteRendererComponent *s1,
ecs_entity_t e2, const SpriteRendererComponent *s2){
    (void)e1;
    (void)e2;
    if (s1 == NULL || s2 == NULL)return 0;
    return s1->sortingOrder - s2->sortingOrder;
}

static void system__init_fn(ecs_iter_t *it)
{
    SpriteRendererComponent *sprite = ecs_term_w_size(it, sizeof(SpriteRendererComponent), 1);

    for (int i = 0; i < it->count; i++)
    {
        sprite[i].key = sprite[i].key == NULL ? "" : sprite[i].key;
        sprite[i].color = ecolor_empty(sprite[i].color) ? WHITE : sprite[i].color;
    }
}

static void system__render_fn(ecs_iter_t *it)
{
    SpriteRendererComponent *sprite = ecs_term_w_size(it, sizeof(SpriteRendererComponent), 1);
    TransformComponent *transform = ecs_term_w_size(it, sizeof(TransformComponent), 2);

    for (int i = 0; i < it->count; i++)
    {
        // Si el key esta en blanco no mostramos...
        if (strlen(sprite[i].key) == 0)
            continue;

        etexture_draw((etexture_desc){
            .source = eresource_get_texture(sprite[i].key),
            .color = sprite[i].color,
            .flipx = sprite[i].flipX,
            .flipy = sprite[i].flipY,
            .transform = transform[i],
        });
    }
}

void ComponentSpritesImport(ecs_world_t *world)
{
    // COMPONENTE SPRITES
    // ---------------------
    ecs_entity_t IdSpriteRendererComponent = ecs_component_init(world, &(ecs_component_desc_t){
        .entity.name = "SpriteRendererComponent",
        .size = sizeof(SpriteRendererComponent),
        .alignment = ECS_ALIGNOF(SpriteRendererComponent),
    });

    ecs_struct_init(world, &(ecs_struct_desc_t){
        .entity.entity = IdSpriteRendererComponent,
           .members = {
                {.name = "key", .type = ecs_id(ecs_string_t)},
                {.name = "color", .type = flower_lookup("CColor")},
                {.name = "flipX", .type = ecs_id(ecs_bool_t)},
                {.name = "flipY", .type = ecs_id(ecs_bool_t)},
                {.name = "sortingOrder", .type = ecs_id(ecs_i8_t)},
            },
    });

    // SYSTEM & OBSERVER COMPONENTE SPRITES
    // ---------------------
    ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = {{.id = IdSpriteRendererComponent}},
        .events = {EcsOnSet, EcsOnAdd},
        .callback = system__init_fn,
    });

    ECS_TAG(world, EventSystemOnRender);

    ecs_system_init(world, &(ecs_system_desc_t){
        .entity = {.name = "EventSystemOnRender", .add = {EventSystemOnRender}},
        .query = {
            .filter.terms = {
                {.id = IdSpriteRendererComponent},
                {.id = flower_lookup("TransformComponent"), .inout = EcsIn},
            },
            .order_by = sprites_sortingOrder,
            .order_by_component = IdSpriteRendererComponent
        },
       .callback = system__render_fn,
    });
}

#include "eactor.h"

// GHASTABLE REG COMPONENTS
#include <glib.h>

#include "component.transform.h"

static ecs_world_t *world;
static GHashTable *hash_table;

void ecs_flecs_init(void)
{
    world = ecs_init();

    hash_table = g_hash_table_new(g_str_hash, g_str_equal);

    ComponentTransformImport(world);
    ComponentSpritesImport(world);
}

void ecs_flecs_update(void)
{
    ecs_progress(world, 0);
}

void ecs_flecs_close(void)
{
    g_hash_table_destroy(hash_table);
}

ecs_world_t *eactor_get_world(void)
{
    return world;
}

// ECOMPONENT

void component_custom_register_global(const char *name, ecs_entity_t id)
{
    g_hash_table_insert(hash_table, name, id);
}

ecs_entity_t component_custom_load_global(const char *name)
{
    return g_hash_table_lookup(hash_table, name);
}

// ESYSTEM


// EACTOR

actor actor_new(const char *name)
{
    return ecs_new_entity(world, name);
}

void actor_set_ptr(actor a, const char *name, size_t size, void *components)
{
    ecs_entity_t cmp = g_hash_table_lookup(hash_table, name);
    if (cmp > 0)
    {
        ecs_set_id(world, a, cmp, size, components);
    }
}

// EACTOR SERIALIZE

char *actor_serialize_data(actor a)
{
#define ECS_ENTITY_TO_JSON (ecs_entity_to_json_desc_t) {\
    true, false, false, false, false, false, true, false, false, false, true }

    ecs_entity_to_json_desc_t desc = ECS_ENTITY_TO_JSON;
    desc.serialize_values = true;

    char *buffer = ecs_entity_to_json(world, a, &desc);
    // ecs_os_free(buffer);
    return buffer;
}

actor actor_deserialize_data(const char *data)
{
    // {"path":"Entity11", "ids":[["Position"], ["Scale"]], "values":[{"x":10, "y":0, "z":10}, {"x":1, "y":1, "z":1}]}
    // const char *buffer = ecs_parse_json(world, data, )

    actor a = actor_new("Entity11");
    // procesador de componentes
    ecs_entity_t cmp = g_hash_table_lookup(hash_table, "EcsPosition");
    void *ptr = ecs_get_mut_id(world, a, cmp, 0);

    // procesador de datos de componentes
    ecs_meta_cursor_t cur = ecs_meta_cursor(world, cmp, ptr);
    ecs_meta_push(&cur);
    ecs_meta_set_float(&cur, 10);
    ecs_meta_next(&cur);
    ecs_meta_set_float(&cur, 0);
    ecs_meta_next(&cur);
    ecs_meta_set_float(&cur, 10);
    ecs_meta_pop(&cur);

    // aplicamos el proceso
    ecs_meta_set_entity(&cur, a);

    return a;
}

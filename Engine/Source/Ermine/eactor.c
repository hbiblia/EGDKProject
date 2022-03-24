#include "eactor.h"

// GHASTABLE REG COMPONENTS
#include <glib.h>

#include "component.transform.h"
#include "component.sprites.h"

static ecs_world_t *world;
static GHashTable *hash_table;
static actor prefab_default;
static ecs_entity_t pipeline[32]; // no working

// 
// ------------------
void ecs_flecs_init(void)
{
    // Flecs init
    world = ecs_init();

    // Donde registramos los componentes.
    hash_table = g_hash_table_new(g_str_hash, g_str_equal);

    // Creamos pipeline-custom
    actor_pipeline_custom_init(world);

    // iniciamos los componentes por defecto.
    ComponentBaseImport(world);
    ComponentTransformImport(world);
    ComponentSpritesImport(world);

    // Creamos el prefabricado por defecto.
    prefab_default = actor_prefab_default();

}

void ecs_flecs_progress(void)
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

// PIPELINE CUSTOM
// ------------------

void actor_pipeline_custom_init(ecs_world_t *world)
{
}
ecs_entity_t actor_pipeline_get(int p)
{
}
void actor_pipeline_run(int p)
{
}

// ECOMPONENT
// ------------------

void component_custom_global_registre(const char *name, ecs_entity_t id)
{
    g_hash_table_insert(hash_table, name, id);
}

ecs_entity_t component_custom_global_load(const char *name)
{
    return g_hash_table_lookup(hash_table, name);
}

// ESYSTEM
// ------------------

void actor_system_run(const char *query)
{
    ecs_query_t *q = ecs_query_new(world, query);
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            ecs_run(world, it.entities[i], 0, NULL);
        }
    }
}

// EACTOR
// ------------------

actor actor_new(const char *name)
{
    actor e = ecs_new_entity(world, name);
    // ecs_add_pair(world, e, EcsIsA, prefab_default);
    actor_set(e, EcsPosition, {0});
    actor_set(e, EcsScale, {1, 1, 1});
    actor_set(e, EcsRotation, {0});
    return e;
}

actor actor_prefab_default(void)
{
    actor e = ecs_new_prefab(world, "Actor");
    actor_set(e, EcsPosition, {0});
    actor_set(e, EcsScale, {1, 1, 1});
    actor_set(e, EcsRotation, {0});
    return e;
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
// ------------------

char *actor_serialize_data(actor a)
{
#define ECS_ENTITY_TO_JSON (ecs_entity_to_json_desc_t){ \
    true, false, false, false, false, false, true, false, false, false, true}

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

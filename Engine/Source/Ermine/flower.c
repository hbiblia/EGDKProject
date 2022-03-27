#include "flower.h"

#include "component.transform.h"
#include "component.sprites.h"

static ecs_world_t *world;

static int entity_len_world = 0;

//
// ------------------
void ecs_flecs_init(void)
{
    // Flecs init
    world = ecs_init();

    // iniciamos los componentes por defecto.
    ComponentBaseImport(world);
    ComponentTransformImport(world);
    ComponentSpritesImport(world);
}

void ecs_flecs_progress(void)
{
    ecs_progress(world, 0);
}

void ecs_flecs_close(void)
{
    ecs_fini(world);
}

ecs_world_t *flower_get_world(void)
{
    return world;
}

ecs_entity_t actor_get_lookup(const char *name)
{
    return ecs_lookup(world, name);
}

// ------------------
// FLOWER:ENTITY
// ------------------

/*
 * Verificamos que la entidad este deshabilitada
 *
 */

bool flower_is_disabled(ecs_entity_t entity)
{
    return ecs_has_id(world, entity, EcsDisabled);
}

/*
 * Verificamos que la entidad este habilitada
 *
 */

bool flower_is_enabled(ecs_entity_t entity)
{
    return !ecs_has_id(world, entity, EcsDisabled);
}

/*
 * Deshabilitamos o Habilitamos una entidad
 *
 */

void flower_enable(ecs_entity_t entity, bool enabled)
{
    ecs_enable(world, entity, enabled);
}

void flower_set_component_ptr(ecs_entity_t entity, const char *name, size_t size, void *components)
{
    ecs_entity_t cmp = actor_get_lookup(name);
    if (cmp > 0)
    {
        ecs_set_id(world, entity, cmp, size, components);
    }
}

void flower_set_component_empty(actor a, ecs_entity_t component)
{
    ecs_add_id(world, a, component);
}

/*
 * Clonamos una entidad y sus componentes.
 *
 */

void flower_entity_clone_new(ecs_entity_t source)
{
    char *name = ecs_get_name(world, source);
    ecs_entity_t n = ecs_clone(world, 0, source, false);
    ecs_set_name(world, n, STRDUPPF("%s%d", name, entity_len_world));

    // Clonar es lo mismo
    entity_len_world++;
}

/*
 * Borramos una entidad del mundo.
 *
 */

void flower_entity_remove(ecs_entity_t entity)
{
    if (ecs_is_alive(world, entity) && ecs_is_valid(world, entity))
    {
        printf("INFO: Delete entity [ID:%u][NAME:%s]\n", entity, ecs_get_name(world, entity));
        // ecs_enable(world, entity, false);
        // ecs_delete(world, entity);
        // ecs_entity_t parent = ecs_get_pair(world, entity);
        // ecs_remove_pair(world, entity, EcsChildOf, entity);
    }
}

/*
 * Creamos una entidad basica.
 *
 */

ecs_entity_t flower_entity_new(const char *name, ecs_entity_t parent, bool uid)
{
    char *new_name = uid ? STRDUPPF("%s%d", name, entity_len_world) : name;

    ecs_entity_t entity = ecs_new_entity(world, new_name);
    // Siempre se agrega a un padre Root o otra entidad.
    if (parent > 0)
    {
        ecs_add_pair(world, entity, EcsChildOf, parent);
    }
    // Todos tienen el mismo componente si esta en la escena.
    actor_set(entity, TransformComponent, {.scale = {1, 1, 1}});

    entity_len_world++;

    return entity;
}

// ------------------
//
// ------------------

/*
 * Nos permite obtener el identificador actor de
 * un componente o un actor en si segun su nombre.
 *
 */

actor flower_lookup(const char *name)
{
    return ecs_lookup(world, name);
}

/*
 * Ejecutamos un sistema custom.
 *
 */

void flower_internal_system_run(const char *system_str)
{
    ecs_query_t *q = ecs_query_new(world, system_str);
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            ecs_run(world, it.entities[i], 0, NULL);
        }
    }
    ecs_query_fini(q);
}

// FLOWER::SERIALIZE & DESERIALIZE
// ------------------

/*
 * Nos permite serializar el world de flecs
 * y nos entrega un buffer string con los datos.
 *
 *
 */

const char *flower_internal_serialize(void)
{
    // JSON FLECS PREPARE
#define ECS_ENTITY_TO_JSON (ecs_entity_to_json_desc_t){ \
    true, false, false, false, false, false, true, false, false, false, true}

    ecs_entity_to_json_desc_t desc = ECS_ENTITY_TO_JSON;
    desc.serialize_values = true;

    // Obtenemos todas las entidades en el mundo
    // que estan creadas por el usuario.
    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
                                               .filter.terms = {
                                                   {.id = flower_lookup("TransformComponent"), .inout = EcsIn},
                                               },
                                           });

    GString *buffer_json = g_string_new("[");

    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            char *buffer = ecs_entity_to_json(world, it.entities[i], &desc);
            buffer_json = g_string_append(buffer_json, buffer);
            if (i != (it.count - 1))
                buffer_json = g_string_append(buffer_json, ",");
        }
    }
    buffer_json = g_string_append(buffer_json, "]");
    return g_string_free(buffer_json, false);
}

/*
 * Nos permite deserializar los datos de un archivo,
 * esto crea las entidades nuevas en el world de flecs.
 *
 */

void flower_internal_deserialize(const char *filename)
{
    // {"path":"Entity11", "ids":[["Position"], ["Scale"]], "values":[{"x":10, "y":0, "z":10}, {"x":1, "y":1, "z":1}]}
    // const char *buffer = ecs_parse_json(world, data, )

    // actor a = actor_new("Entity11");
    // // procesador de componentes
    // ecs_entity_t cmp = actor_get_lookup("CPosition");
    // void *ptr = ecs_get_mut_id(world, a, cmp, 0);

    // // procesador de datos de componentes
    // ecs_meta_cursor_t cur = ecs_meta_cursor(world, cmp, ptr);
    // ecs_meta_push(&cur);
    // ecs_meta_set_float(&cur, 10);
    // ecs_meta_next(&cur);
    // ecs_meta_set_float(&cur, 0);
    // ecs_meta_next(&cur);
    // ecs_meta_set_float(&cur, 10);
    // ecs_meta_pop(&cur);

    // // aplicamos el proceso
    // ecs_meta_set_entity(&cur, a);
}

#include "ermine.h"
#include "ermine-flower.h"
#include "components.h"

static ecs_world_t *world;

static int entity_len_world = 0;

static GSList *list_components = NULL;

//
// ------------------
void ecs_flecs_init(void)
{
    // Flecs init
    world = ecs_init();

    // iniciamos los componentes por defecto.
    components_init();
}

void flower_reset_entity_world_len(void)
{
    entity_len_world = 0;
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

void flower_component_append_list(const char *name)
{
    if (strcmp(name, "InfoComponent") == 0)
    {
        return;
    }
    list_components = g_slist_append(list_components, name);
}

GSList *flower_component_get_list(void)
{
    return list_components;
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

void flower_set_component_empty(ecs_entity_t a, ecs_entity_t component)
{
    ecs_add_id(world, a, component);
}

/*
 * Clonamos una entidad y sus componentes.
 *
 */

void flower_entity_clone_new(ecs_entity_t source)
{
    ecs_entity_t new_entity = ecs_clone(world, 0, source, true);
    flower_info_set_id(new_entity, entity_len_world);

    entity_len_world++;
}

/*
 * Borramos una entidad del mundo.
 *
 */

void flower_entity_remove(ecs_entity_t entity)
{
    printf("INFO: Delete entity [ID:%u][NAME:%s]\n", entity, flower_info_get_name(entity));
    ecs_delete(world, entity);
}

/*
 * Creamos una entidad basica.
 *
 */

ecs_entity_t flower_entity_new_custom(const char *name, ecs_entity_t parent, bool uid, bool name_real)
{
    char *new_name = uid ? STRDUPPF("%s%d", name, entity_len_world) : name;

    ecs_entity_t entity = name_real ? ecs_set_name(world, 0, name) : ecs_new_id(world);
    if (parent > 0)
    {
        ecs_add_pair(world, entity, EcsChildOf, parent);
    }
    // Todos tienen el mismo componente.
    actor_set(entity, InfoComponent, {.name = new_name, .id = entity_len_world});
    actor_set(entity, TransformComponent, {.scale = {1, 1, 1}});

    entity_len_world++;

    return entity;
}

ecs_entity_t flower_entity_new(const char *name, ecs_entity_t parent)
{
    return flower_entity_new_custom(name, parent, true, false);
}

// ------------------
//
// ------------------

/*
 * Nos permite obtener el identificador actor de
 * un componente o un actor en si segun su nombre.
 *
 */

ecs_entity_t flower_lookup(const char *name)
{
    return ecs_lookup(world, name);
}

/*
 * Obtenemos el InfoName de la entidad
 *
 */

char *flower_info_get_name(ecs_entity_t entity)
{
    InfoComponent *component_ptr = ecs_get_id(world, entity, flower_lookup("InfoComponent"));
    return component_ptr->name;
}

/*
 * Cambiamos el InfoName de la entidad
 *
 */

void flower_info_set_name(ecs_entity_t entity, const char *name)
{
    InfoComponent *component_ptr = ecs_get_id(world, entity, flower_lookup("InfoComponent"));
    component_ptr->name = g_strdup(name);
}

/*
 * Cambiamos el Infoid de la entidad
 *
 */
void flower_info_set_id(ecs_entity_t entity, int id)
{
    InfoComponent *component_ptr = ecs_get_id(world, entity, flower_lookup("InfoComponent"));
    component_ptr->id = id;
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

JSON_Value *flower_internal_process_data(JSON_Value *value)
{
    JSON_Object *json_data = json_value_get_object(value);
    JSON_Array *components_name = json_object_get_array(json_data, "ids");
    JSON_Array *components_value = json_object_get_array(json_data, "values");

    JSON_Value *new_value = json_parse_string("{\"components\":[], \"children\":[]}");
    JSON_Array *components = json_object_get_array(json_object(new_value), "components");

    for (int i = 0; i < json_array_get_count(components_name); i++)
    {
        JSON_Array *name = json_array_get_array(components_name, i);
        JSON_Value *value = json_array_get_value(components_value, i);

        // data human
        char *name_cmp = json_array_get_string(name, 0);

        // new object
        JSON_Value *vcomponent = json_value_init_object();
        JSON_Object *bcomponent = json_value_get_object(vcomponent);
        json_object_set_string(bcomponent, "name", name_cmp);
        json_object_set_value(bcomponent, "value", json_parse_string(json_serialize_to_string_pretty(value)));
        json_array_append_value(components, vcomponent);
    }

    return new_value;
}

JSON_Value *flower_internal_serialize(ecs_entity_t entity, JSON_Value *parent)
{
#define ECS_ENTITY_TO_JSON (ecs_entity_to_json_desc_t){ \
    true, false, false, false, false, false, true, false, false, false, false}

    ecs_entity_to_json_desc_t desc = ECS_ENTITY_TO_JSON;
    desc.serialize_values = true;

    // JSON_ENTITY
    char *buffer = ecs_entity_to_json(world, entity, &desc);
    JSON_Value *value_data = json_parse_string(buffer);
    ecs_os_free(buffer);

    // JSON_ENTITY_PROCESS
    value_data = flower_internal_process_data(value_data);

    // QUERY_ENTITY_CHILDREN
    ecs_query_t *querys = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {
            {.id = ecs_childof(entity), .inout = EcsIn},
            {.id = EcsDisabled, .oper = EcsOptional},
        },
    });

    ecs_iter_t it = ecs_query_iter(world, querys);
    while (ecs_query_next(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            ecs_entity_t e = it.entities[i];
            if (json_object_has_value(json_object(value_data), "children"))
            {
                JSON_Object *children = json_object_get_array(json_object(value_data), "children");
                flower_internal_serialize(e, children);
            }
        }
    }
    ecs_query_fini(querys);

    // PARENT
    if (parent != NULL)
    {
        json_array_append_value(parent, value_data);
    }

    return value_data;
}

void flower_internal_deserialize(JSON_Value *value)
{
    JSON_Object *json_data = json_value_get_object(value);

    JSON_Array *components = json_object_get_array(json_data, "components");
    JSON_Array *children = json_object_get_array(json_data, "children");

    // ermine_scene_init();

    // flower_internal_json_parse_component(ermine_scene_get(), components);

    // flower_entity_new()

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

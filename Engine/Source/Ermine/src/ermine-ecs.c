#include "ermine-ecs.h"
#include "parson/parson.h"
#include <glib.h>

#include "ermine-ccolor.h"
#include "ermine-cshapes.h"
#include "ermine-cmath.h"
#include "ermine-ctransform.h"
#include "ermine-crenderer.h"
#include "ermine-ctexture.h"
#include "ermine-cbaseinfo.h"
#include "ermine-c-background.h"

#include "ermine-string.h"

static ecs_world_t *world;

static ecs_entity_t EcsRootOf;

static GHashTable *metatable = NULL;

void ermine_ecs_init(void)
{
    world = ecs_init();

    // tabla hash para guardar la info de los componentes unicos.
    metatable = g_hash_table_new(g_str_hash, g_str_equal);

    // Iniciamos los componentes base
    ComponentBaseinfocomponentImport(world);
    ComponentBaseRendererImport(world);
    ComponentBaseMathImport(world);
    ComponentBaseTransformImport(world);
    ComponentBaseColorImport(world);
    ComponentTexture(world);
    ComponentBaseShapesImport(world);
    ComponentBackgroundTilingImport(world);

    // Root create
    EcsRootOf = ermine_entity_new();
    ecs_set_name(world, EcsRootOf, "Root");
    ermine_entity_set_name(EcsRootOf, "Root");
}

void ermine_ecs_close(void)
{
    g_hash_table_destroy(metatable);
    ecs_fini(world);
}

bool ermine_ecs_progress(void)
{
    return ecs_progress(world, 0);
}

const ecs_world_t *ermine_ecs_get_world(void)
{
    return world;
}

// entity root
ecs_entity_t ermine_entity_get_root(void)
{
    return EcsRootOf;
}

// entity
ecs_entity_t ermine_entity_spawn(void)
{
    ecs_entity_t e = ermine_entity_new();
    ermine_entity_set_parent(EcsRootOf, e);
    return e;
}

ecs_entity_t ermine_entity_new(void)
{
    ecs_entity_t e = ecs_new_id(world);
    ermine_component_set(e, baseinfocomponent, {.name = ermine_strdup_printf("Entity%u", e)});
    ermine_component_set(e, etransform, {.position = {0, 0}, .scale = {1, 1}, .angle = 0.0f});
    return e;
}

ecs_entity_t ermine_entity_clone(ecs_entity_t src)
{
    ecs_entity_t e = ecs_clone(world, 0, src, true);
    ermine_entity_set_name(e, ermine_strdup_printf("cEntity%d", e));

    // clonamos sus hijos si tiene.
    ecs_query_t *query = ermine_entity_query(&(ecs_query_desc_t){
        .filter.terms = {
            {.id = ermine_entity_lookup("etransform")},
            {.id = ermine_entity_get_parent(src)},
            {.id = EcsDisabled, .oper = EcsOptional},
        },
    });
    ecs_iter_t it = ermine_entity_query_iter(query);
    while (ermine_entity_query_next(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            ecs_entity_t clone_child = ermine_entity_clone(it.entities[i]);
            ermine_entity_set_parent(e, clone_child);
        }
    }
    ermine_entity_query_free(query);

    return e;
}

void ermine_entity_delete(ecs_entity_t e)
{
    if (ermine_entity_is_valid(e))
        ecs_delete(world, e);
}

void ermine_entity_set_parent(ecs_entity_t parent, ecs_entity_t child)
{
    ecs_add_pair(world, child, EcsChildOf, parent);
}

ecs_entity_t ermine_entity_lookup(const char *name)
{
    return ecs_lookup(world, name);
}

void ermine_entity_set_name(ecs_entity_t e, const char *name)
{
    baseinfocomponent *c = ermine_component_get(e, "baseinfocomponent");
    c->name = ermine_strdup(name);
}

const char *ermine_entity_get_name(ecs_entity_t e)
{
    baseinfocomponent *c = ermine_component_get(e, "baseinfocomponent");
    return c->name;
}

bool ermine_entity_is_enabled(ecs_entity_t e)
{
    return !ecs_has_id(world, e, EcsDisabled);
}

bool ermine_entity_is_disabled(ecs_entity_t e)
{
    return ecs_has_id(world, e, EcsDisabled);
}

bool ermine_entity_is_valid(ecs_entity_t e)
{
    return ecs_is_valid(world, e);
}

ecs_entity_t ermine_entity_get_type(ecs_entity_t e)
{
    return ecs_get_type(world, e);
}

ecs_entity_t ermine_entity_get_parent(ecs_entity_t e)
{
    return ecs_childof(e);
}

bool ermine_entity_is_parent(ecs_entity_t e)
{
    return ecs_count_id(world, ecs_pair(EcsChildOf, e)) > 0 ? true : false;
}

// query
void *ermine_iter_get_ptr(ecs_iter_t *it, size_t component, int32_t index)
{
    return ecs_term_w_size(it, component, index);
}

ecs_query_t *ermine_entity_query(const ecs_query_desc_t *query_desc)
{
    return ecs_query_init(world, query_desc);
}

ecs_iter_t ermine_entity_query_iter(ecs_query_t *q)
{
    return ecs_query_iter(world, q);
}

bool ermine_entity_query_next(ecs_iter_t *it)
{
    return ecs_query_next(it);
}

void ermine_entity_query_free(ecs_query_t *q)
{
    ecs_query_fini(q);
}

// filter
ecs_filter_t ermine_entity_filter(const ecs_filter_desc_t *filter_desc)
{
    ecs_filter_t f;
    ecs_filter_init(world, &f, filter_desc);
    return f;
}

ecs_iter_t ermine_entity_filter_iter(const ecs_filter_t *q)
{
    return ecs_filter_iter(world, q);
}

bool ermine_entity_filter_next(ecs_iter_t *it)
{
    return ecs_filter_next(it);
}

void ermine_entity_filter_free(ecs_filter_t *q)
{
    ecs_filter_fini(q);
}


// component
void ermine_component_set_empty(ecs_entity_t e, const char *component)
{
    ecs_add_id(world, e, ecs_lookup(world, component));
}

void ermine_component_set_ptr(ecs_entity_t entity, ecs_id_t id, size_t size, const void *ptr)
{
    ecs_set_id(world, entity, id, size, ptr);
}

void *ermine_component_get(ecs_entity_t e, const char *component)
{
    return ecs_get_id(world, e, ermine_entity_lookup(component));
}

ecs_entity_t ermine_component_init(ecs_entity_t e_cmp, const char *id, size_t size, size_t alignment)
{
    ecs_entity_t out_cmp1 = ecs_component_init(world,
                                               &(ecs_component_desc_t){
                                                   .entity.entity = e_cmp,
                                                   .entity.name = id,
                                                   .entity.symbol = id,
                                                   .size = size,
                                                   .alignment = alignment,
                                               });
    return out_cmp1;
}

void ermine_component_remove(ecs_entity_t e, const char *component)
{
    ecs_remove_id(world, e, ermine_entity_lookup(component));
}

GList *ermine_component_list(void)
{
    return g_hash_table_get_values(metatable);
}

// meta component
void ermine_component_meta_set_prop(ecs_entity_t e, const char *component, const char *key, void *data)
{
}

void *ermine_component_meta_get_prop(ecs_entity_t e, const char *component, const char *key)
{
}

ecs_meta_desc_t *ermine_component_meta_lookup(const char *id)
{
    return g_hash_table_lookup(metatable, id);
}

void ermine_component_meta_init(ecs_entity_t e_cmp, const char *id, ecs_meta_desc_t *meta)
{
    meta->id = ermine_strdup(id);

    ecs_meta_desc_t *meta_new = malloc(sizeof(ecs_meta_desc_t));
    memcpy(meta_new, meta, sizeof(ecs_meta_desc_t) * 1);

    // guardamos el meta
    g_hash_table_insert(metatable, id, meta_new);

    // ecs_struct_desc_t
    ecs_struct_desc_t m_desc = {0};

    for (size_t i = 0; i < META_MAX_PROPERTY_CACHE_SIZE; i++)
    {
        if (meta->property[i].name == NULL)
            break;

        // Si serialize es false
        if (!meta->property[i].serialize)
            continue;

        const char *name = meta->property[i].name;
        const char *type = meta->property[i].type;

        ecs_entity_t type_ecs = 0;

        if (strcmp(type, "float") == 0)
        {
            type_ecs = ecs_id(ecs_f32_t);
        }
        else if (strcmp(type, "int") == 0)
        {
            type_ecs = ecs_id(ecs_i32_t);
        }
        else if (strcmp(type, "string") == 0)
        {
            type_ecs = ecs_id(ecs_string_t);
        }
        else
        {
            type_ecs = ecs_lookup(world, type);
        }
        m_desc.members[i] = (ecs_member_t){.name = name, .type = type_ecs};
    }

    m_desc.entity.entity = e_cmp;
    // ecs_struct_init(world, &m_desc);
}

// system
void ermine_ecs_run(const char *query_str)
{
    ecs_query_t *q = ecs_query_new(world, query_str);
    if (q == NULL)
        return;
    
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

ecs_entity_t ermine_system_init(const ecs_system_desc_t *desc)
{
    return ecs_system_init(world, desc);
}

// serialize funcs
static JSON_Value *ermine_internal_process_serialize(JSON_Value *value)
{
    JSON_Object *json = json_value_get_object(value);
    JSON_Array *cnames = json_object_get_array(json, "ids");
    JSON_Array *cvalues = json_object_get_array(json, "values");

    JSON_Value *new_data = json_parse_string("{\"components\":[],\"children\":[]}");
    JSON_Array *components = json_object_get_array(json_object(new_data), "components");

    for (int i = 0; i < json_array_get_count(cnames); i++)
    {
        JSON_Array *names = json_array_get_array(cnames, i);
        JSON_Array *values = json_array_get_value(cvalues, i);

        char *name = json_array_get_string(names, 0);

        JSON_Value *vcomponent = json_value_init_object();
        JSON_Object *ocomponent = json_value_get_object(vcomponent);
        json_object_set_string(ocomponent, "name", name);
        json_object_set_value(ocomponent, "value", json_parse_string(json_serialize_to_string_pretty(cvalues)));
        json_array_append_value(components, vcomponent);
    }
}

JSON_Value *ermine_ecs_serialize(ecs_entity_t entity, JSON_Value *parent)
{
#define ECS_ENTITY_TO_JSON \
    (ecs_entity_to_json_desc_t){true, false, false, false, false, false, true, false, false, false, false}

    ecs_entity_to_json_desc_t desc = ECS_ENTITY_TO_JSON;
    desc.serialize_values = true;

    char *buffer = ecs_entity_to_json(world, entity, &desc);
    JSON_Value *value_data = json_parse_string(buffer);
    ecs_os_free(buffer);

    value_data = ermine_internal_process_serialize(value_data);

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
                ermine_ecs_serialize(e, children);
            }
        }
    }

    ecs_query_fini(querys);

    if (parent != NULL)
    {
        json_array_append_value(parent, value_data);
    }

    return value_data;
}

void ermine_ecs_deserialize(JSON_Value *value)
{
}

#ifndef ERMINE_ECS_H
#define ERMINE_ECS_H

#include <stdio.h>
#include <stdbool.h>
#include "ermine.h"

#include "parson/parson.h"
#include "flecs/flecs.h"
#include <glib.h>

#define L ermine_entity_lookup
#define W ermine_ecs_get_world()

#define META_MAX_PROPERTY_CACHE_SIZE 32

typedef struct ecs_meta_property_desc_t
{
    char *name;
    char *type;
    void *value;
    bool barray;
    bool serialize;
    bool readonly;
    float step;     // valores numericos
} ecs_meta_property_desc_t;

typedef struct ecs_meta_desc_t
{
    char *label;
    char *id;
    bool public;
    ecs_meta_property_desc_t property[META_MAX_PROPERTY_CACHE_SIZE];
} ecs_meta_desc_t;

#define ermine_component_set(entity, component, ...) \
    ermine_component_set_ptr(entity, ermine_entity_lookup(#component), sizeof(component), &(component)__VA_ARGS__)

#define ermine_component(id, ...)                                                   \
    {                                                                               \
        ecs_entity_t ecs_id(id) = 0;                                                \
        ermine_component_init(ecs_id(id), #id, sizeof(id), ECS_ALIGNOF(id));        \
        ermine_component_meta_init(ecs_id(id), #id, &(ecs_meta_desc_t)__VA_ARGS__); \
    }

#define ermine_system(id, kind, ...)            \
    {                                           \
        ecs_entity_t ecs_id(id);                \
        ecs_system_desc_t desc = {0};           \
        desc.entity.name = #id;                 \
        desc.entity.add[0] = kind;              \
        desc.query.filter.expr = #__VA_ARGS__;  \
        desc.callback = id;                     \
        ecs_id(id) = ermine_system_init(&desc); \
    }

#define ermine_system_order(id, component, kind, ...)                      \
    {                                                                      \
        ecs_entity_t ecs_id(id);                                           \
        ecs_system_desc_t desc = {0};                                      \
        desc.entity.name = #id;                                            \
        desc.entity.add[0] = kind;                                         \
        desc.query.filter.expr = #__VA_ARGS__;                             \
        desc.query.order_by = (ecs_order_by_action_t)component##_fn_order; \
        desc.query.order_by_component = ermine_entity_lookup(#component);  \
        desc.callback = id;                                                \
        ecs_id(id) = ermine_system_init(&desc);                            \
    }

#define ermine_iter_get(it, component, i) \
    ermine_iter_get_ptr(it, sizeof(component), i);

ermine_private void ermine_ecs_init(void);
ermine_private void ermine_ecs_close(void);
ermine_private bool ermine_ecs_progress(void);
ermine_public const ecs_world_t *ermine_ecs_get_world(void);

ermine_public ecs_entity_t ermine_entity_get_root(void);

ermine_public ecs_entity_t ermine_entity_spawn(void);
ermine_public ecs_entity_t ermine_entity_new(void);
ermine_public ecs_entity_t ermine_entity_clone(ecs_entity_t src);
ermine_public void ermine_entity_delete(ecs_entity_t e);
ermine_public void ermine_entity_set_parent(ecs_entity_t parent, ecs_entity_t child);
ermine_public ecs_entity_t ermine_entity_lookup(const char *name);
ermine_public const char *ermine_entity_get_name(ecs_entity_t e);
ermine_public bool ermine_entity_is_valid(ecs_entity_t e);
ermine_public ecs_entity_t ermine_entity_get_type(ecs_entity_t e);
ermine_public ecs_entity_t ermine_entity_get_parent(ecs_entity_t e);
ermine_public bool ermine_entity_is_parent(ecs_entity_t e);

// query
ermine_public ecs_query_t *ermine_entity_query(const ecs_query_desc_t *query_desc);
ermine_public ecs_iter_t ermine_entity_query_iter(ecs_query_t *q);
ermine_public bool ermine_entity_query_next(ecs_iter_t *it);
ermine_public void ermine_entity_query_free(ecs_query_t *q);

// filter
ermine_public ecs_filter_t ermine_entity_filter(const ecs_filter_desc_t *filter_desc);
ermine_public ecs_iter_t ermine_entity_filter_iter(const ecs_filter_t *q);
ermine_public bool ermine_entity_filter_next(ecs_iter_t *it);
ermine_public void ermine_entity_filter_free(ecs_filter_t *q);

// it
ermine_public void *ermine_iter_get_ptr(ecs_iter_t *it, size_t component, int index);

// component
ermine_public ecs_entity_t ermine_component_init(ecs_entity_t e_cmp, const char *id, size_t size, size_t alignment);
ermine_public void *ermine_component_get(ecs_entity_t e, const char *component);
ermine_public void ermine_component_set_ptr(ecs_entity_t entity, ecs_id_t id, size_t size, const void *ptr);
ermine_public GList *ermine_component_list(void);
ermine_public void ermine_component_set_empty(ecs_entity_t e, const char *component);
ermine_public void ermine_component_remove(ecs_entity_t e, const char *component);

// meta component
ermine_public void ermine_component_meta_init(ecs_entity_t e_cmp, const char *id, ecs_meta_desc_t *meta);
ermine_public void ermine_component_meta_set_prop(ecs_entity_t e, const char *component, const char *key, void *data);
ermine_public void *ermine_component_meta_get_prop(ecs_entity_t e, const char *component, const char *key);
ermine_public ecs_meta_desc_t *ermine_component_meta_lookup(const char *id);

// system
ermine_public void ermine_ecs_run(const char *query_str);
ermine_public ecs_entity_t ermine_system_init(const ecs_system_desc_t *desc);

// serialize funcs
JSON_Value *ermine_ecs_serialize(ecs_entity_t entity, JSON_Value *parent);
void ermine_ecs_deserialize(JSON_Value *value);

#endif // ERMINE_ECS_H
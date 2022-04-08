#ifndef EFLECS_H
#define EFLECS_H
#include "flecs/flecs.h"
#include <glib.h>

// Componente base
// ------------------------------------
// declaramos todos los datos basicos
// para ser utilizado en cualquier otro
// componente y se pueda serializar.
// ------------------------------------
#include "Components/component.base.h"

enum
{
    EventSystemOnRender
};

#define FLOWER_COMPONENT_INIT(NameComponent)\
    flower_component_append_list(#NameComponent);\
    ECS_META_COMPONENT(flower_get_world(), NameComponent)

ermine_public void flower_reset_entity_world_len(void);

ermine_public void ecs_flecs_init(void);

ermine_public void ecs_flecs_progress(void);

ermine_public void ecs_flecs_close(void);

ermine_public ecs_world_t *flower_get_world(void);

ermine_public ecs_entity_t actor_get_lookup(const char *name);

ermine_public void flower_component_append_list(const char *name);

ermine_public GSList *flower_component_get_list(void);

// PIPELINE CUSTOM
// ------------------

// ECOMPONENT
// ------------------

ermine_public ecs_entity_t component_custom_global_load(const char *name);
#define ECS_COMPONENT_ID component_custom_global_load

// ESYSTEM
// ------------------

ermine_public void actor_system_run(const char *query);

// ------------------
// FLOWER:ENTITY
// ------------------

ermine_public bool flower_is_disabled(ecs_entity_t entity);

ermine_public bool flower_is_enabled(ecs_entity_t entity);

ermine_public void flower_enable(ecs_entity_t entity, bool enabled);

ermine_public void flower_set_component_ptr(ecs_entity_t entity, const char *name, size_t size, void *components);

#define actor_set(a, c, ...) flower_set_component_ptr(a, #c, sizeof(c), &(c)__VA_ARGS__)

ermine_public void flower_set_component_empty(ecs_entity_t a, ecs_entity_t component);

ermine_public void flower_entity_clone_new(ecs_entity_t source);

ermine_public void flower_entity_remove(ecs_entity_t entity);

ermine_public ecs_entity_t flower_entity_new_custom(const char *name, ecs_entity_t parent, bool uid, bool name_real);

ermine_public ecs_entity_t flower_entity_new(const char *name, ecs_entity_t parent);

// ------------------
//
// ------------------

ermine_public ecs_entity_t flower_lookup(const char *name);

ermine_public char *flower_info_get_name(ecs_entity_t entity);

ermine_public void flower_info_set_name(ecs_entity_t entity, const char *name);

ermine_public void flower_info_set_id(ecs_entity_t entity, int id);

ermine_public void flower_internal_system_run(const char *system_str);

// ------------------
// FLOWER SERIALIZE
// ------------------

ermine_public JSON_Value *flower_internal_serialize(ecs_entity_t entity, JSON_Value *value_o);

ermine_public void flower_internal_deserialize(JSON_Value *value);

#endif // EFLECS_H

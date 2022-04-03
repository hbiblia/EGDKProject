#ifndef EFLECS_H
#define EFLECS_H
#include "flecs/flecs.h"

// Componente base
// ------------------------------------
// declaramos todos los datos basicos
// para ser utilizado en cualquier otro
// componente y se pueda serializar.
// ------------------------------------
#include "component.base.h"

enum
{
    EventSystemOnRender
};

#define FLOWER_COMPONENT_INIT(NameComponent)\
    flower_component_append_list(#NameComponent);\
    ECS_META_COMPONENT(flower_get_world(), NameComponent)

void ecs_flecs_init(void);

void ecs_flecs_progress(void);

void ecs_flecs_close(void);

ecs_world_t *flower_get_world(void);

ecs_entity_t actor_get_lookup(const char *name);

void flower_component_append_list(const char *name);

GSList *flower_component_get_list(void);

// PIPELINE CUSTOM
// ------------------

// ECOMPONENT
// ------------------

ecs_entity_t component_custom_global_load(const char *name);
#define ECS_COMPONENT_ID component_custom_global_load

// ESYSTEM
// ------------------

void actor_system_run(const char *query);

// ------------------
// FLOWER:ENTITY
// ------------------

bool flower_is_disabled(ecs_entity_t entity);

bool flower_is_enabled(ecs_entity_t entity);

void flower_enable(ecs_entity_t entity, bool enabled);

void flower_set_component_ptr(ecs_entity_t entity, const char *name, size_t size, void *components);
#define actor_set(a, c, ...) flower_set_component_ptr(a, #c, sizeof(c), &(c)__VA_ARGS__)

void flower_set_component_empty(ecs_entity_t a, ecs_entity_t component);

void flower_entity_clone_new(ecs_entity_t source);

void flower_entity_remove(ecs_entity_t entity);

ecs_entity_t flower_entity_new(const char *name, ecs_entity_t parent, bool uid, bool name_real);

// ------------------
//
// ------------------

ecs_entity_t flower_lookup(const char *name);

char *flower_info_get_name(ecs_entity_t entity);

void flower_info_set_name(ecs_entity_t entity, const char *name);

void flower_info_set_id(ecs_entity_t entity, int id);

void flower_internal_system_run(const char *system_str);

// ------------------
// FLOWER SERIALIZE
// ------------------

EAPI JSON_Value *flower_internal_serialize(ecs_entity_t entity, JSON_Value *value_o);

EAPI void flower_internal_deserialize(const char *filename);

#endif // EFLECS_H

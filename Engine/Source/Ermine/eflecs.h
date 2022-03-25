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

enum {
    EventSystemOnRender
};

#define actor ecs_entity_t

// 

void ecs_flecs_init(void);
void ecs_flecs_progress(void);
void ecs_flecs_close(void);
ecs_world_t *eactor_get_world(void);
ecs_entity_t actor_get_lookup(const char *name);

// PIPELINE CUSTOM
// ------------------

// ECOMPONENT
// ------------------

ecs_entity_t component_custom_global_load(const char *name);
#define ECS_COMPONENT_ID component_custom_global_load

// ESYSTEM
// ------------------

void actor_system_run(const char *query);

// EACTOR
// ------------------

actor actor_new(const char *name);

actor actor_prefab_default(void);

void actor_set_ptr(actor a, const char *name, size_t size, void *components);

#define actor_set(a, c, ...) actor_set_ptr(a, #c, sizeof(c), &(c)__VA_ARGS__)

void actor_set_empty(actor a, ecs_entity_t component);

// EACTOR SERIALIZE
// ------------------

char *actor_serialize_data(actor a);

actor actor_deserialize_data(const char *data);

#endif // EFLECS_H

#ifndef EFLECS_H
#define EFLECS_H
#include "flecs/flecs.h"

enum {
    EventSystemOnRender
};

#define actor ecs_entity_t

// 

void ecs_flecs_init(void);
void ecs_flecs_progress(void);
void ecs_flecs_close(void);
ecs_world_t *eactor_get_world(void);

// PIPELINE CUSTOM
void actor_pipeline_custom_init(ecs_world_t *world);
ecs_entity_t actor_pipeline_get(int p);
void actor_pipeline_run(int p);

// ECOMPONENT

void component_custom_global_registre(const char *name, ecs_entity_t id);
ecs_entity_t component_custom_global_load(const char *name);

#define ecs_component component_custom_global_registre
#define ecs_component_lookup component_custom_global_load

// ESYSTEM
void actor_system_run(const char *query);

// EACTOR

actor actor_new(const char *name);

actor actor_prefab_default(void);

void actor_set_ptr(actor a, const char *name, size_t size, void *components);

#define actor_set(a, c, ...) actor_set_ptr(a, #c, sizeof(c), &(c)__VA_ARGS__)

// EACTOR SERIALIZE

char *actor_serialize_data(actor a);
actor actor_deserialize_data(const char *data);

#endif // EFLECS_H

#ifndef EFLECS_H
#define EFLECS_H
#include "flecs/flecs.h"

#define actor ecs_entity_t

// 

void ecs_flecs_init(void);

void ecs_flecs_update(void);

void ecs_flecs_close(void);

// ECOMPONENT

void component_custom_register_global(const char *name, ecs_entity_t id);

// ESYSTEM

// EACTOR

actor actor_new(const char *name);

void actor_set_ptr(actor a, const char *name, size_t size, void *components);

#define actor_set(a, c, ...) actor_set_ptr(a, #c, sizeof(c), &(c)__VA_ARGS__)

// EACTOR SERIALIZE

char *actor_serialize_data(actor a);
actor actor_deserialize_data(const char *data);

#endif // EFLECS_H

#ifndef COMPONENT_INFO_H_
#define COMPONENT_INFO_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "flower.h"

ECS_STRUCT(DamageComponent, {
    char *name;
    int id;
});

EAPI void ComponentInfoImport(ecs_world_t *world);

#endif // COMPONENT_INFO_H_

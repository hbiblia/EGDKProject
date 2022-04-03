#ifndef COMPONENT_INFO_H_
#define COMPONENT_INFO_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"

// typedef struct
// {
//     char *name;
//     ECS_PRIVATE
//     int8_t id;
// } InfoComponent;

ECS_STRUCT(InfoComponent, {
    char *name;
    ECS_PRIVATE
    int8_t id;
});

EAPI void ComponentInfoImport(ecs_world_t *world);

#endif // COMPONENT_INFO_H_

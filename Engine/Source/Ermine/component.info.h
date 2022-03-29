#ifndef COMPONENT_INFO_H_
#define COMPONENT_INFO_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "flower.h"

typedef struct
{
    char *name;
    int id;
} InfoComponent;

EAPI void ComponentInfoImport(ecs_world_t *world);

#endif // COMPONENT_INFO_H_

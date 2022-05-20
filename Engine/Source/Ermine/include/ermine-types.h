#ifndef ERMINE_TYPES_H
#define ERMINE_TYPES_H
#include <stdio.h>
#include "ermine.h"
#include "ermine-ecs.h"

typedef struct erect
{
    float x, y, width, height;
} erect;

ermine_private void ComponentBaseTypesImport(ecs_world_t *world);

#endif // ERMINE_TYPES_H

#ifndef ERMINE_COMPONENT_INFO
#define ERMINE_COMPONENT_INFO
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine.h"
#include "ermine-ecs.h"

typedef struct {
    char *name;
    int8_t id;
}baseinfocomponent;

void ComponentBaseinfocomponentImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_COMPONENT_INFO
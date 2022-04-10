#ifndef INFOCOMPONENT_H
#define INFOCOMPONENT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <ermine.h>
#include "ermine-flower.h"
#include "ermine-config.h"

#undef ECS_META_IMPL
#ifndef InfoComponent_EXPORTS
#define ECS_META_IMPL EXTERN // Ensure meta symbols are only defined once
#endif

ECS_STRUCT(InfoComponent, {
    char *name;
    ECS_PRIVATE
    int8_t id;
});

ermine_public void ComponentInfoImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // INFOCOMPONENT_H_
#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"
#include "ermine-config.h"

typedef struct ecolor CColor;
typedef struct evect2 CVec2;
typedef struct evect3 CVec3;
typedef struct erect CRect;

ermine_public void ComponentBaseImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // COMPONENT_BASE_H_

#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"

typedef struct ecolor CColor;
typedef struct evect2 CVec2;
typedef struct evect3 CVec3;
typedef struct erect CRect;

EAPI void ComponentBaseImport(ecs_world_t *world);

#endif // COMPONENT_BASE_H_

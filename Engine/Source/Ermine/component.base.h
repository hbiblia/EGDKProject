#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "eactor.h"

typedef struct ecolor EcsColor;
typedef struct evect2 EcsVect2;
typedef struct evect3 EcsVect3;
typedef struct erect EcsRect;

EAPI void ComponentSpritesImport(ecs_world_t *world);

#endif // COMPONENT_BASE_H_

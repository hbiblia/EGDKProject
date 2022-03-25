#ifndef COMPONENT_TRANSFORM_H_
#define COMPONENT_TRANSFORM_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "eflecs.h"

typedef struct evect3 CPosition;
typedef struct evect3 CScale;
typedef struct evect3 CRotation;
typedef struct etransform CTransform;

EAPI void ComponentTransformImport(ecs_world_t *world);

#endif // COMPONENT_TRANSFORM_H_

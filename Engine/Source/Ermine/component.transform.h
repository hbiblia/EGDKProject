#ifndef COMPONENT_TRANSFORM_H_
#define COMPONENT_TRANSFORM_H_

#include <flecs/flecs.h>
#include <ermine.h>
#include "eactor.h"

typedef struct evect3 EcsPosition;
typedef struct evect3 EcsScale;
typedef struct evect3 EcsRotation;
typedef struct etransform EcsTransform;

EAPI void ComponentTransformImport(ecs_world_t *world);

#endif // COMPONENT_TRANSFORM_H_

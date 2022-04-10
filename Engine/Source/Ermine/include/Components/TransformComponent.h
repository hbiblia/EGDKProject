#ifndef COMPONENT_TRANSFORM_H_
#define COMPONENT_TRANSFORM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"
#include "ermine-config.h"

typedef struct evect3 CPosition;
typedef struct evect3 CScale;
typedef struct evect3 CRotation;
typedef struct etransform TransformComponent;

ermine_public void ComponentTransformImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // COMPONENT_TRANSFORM_H_

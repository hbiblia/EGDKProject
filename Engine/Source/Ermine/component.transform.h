#ifndef COMPONENT_TRANSFORM_H_
#define COMPONENT_TRANSFORM_H_

#include <flecs/flecs.h>
#include <ermine.h>

typedef struct {
    float x;
    float y;
    float z;
}EcsPosition;

typedef struct {
    float x;
    float y;
    float z;
}EcsScale;

typedef struct {
    float x;
    float y;
    float z;
}EcsRotation;

typedef struct {
    EcsPosition position;
    EcsScale scale;
    EcsRotation rotation;
}EcsTransform;

EAPI void ComponentTransformImport(ecs_world_t *world);

#endif // COMPONENT_TRANSFORM_H_

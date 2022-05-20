#ifndef ERMINE_CMATH_H
#define ERMINE_CMATH_H
#include <math.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine.h"
#include "ermine-ecs.h"

typedef struct {
    float x;
    float y;
    float z;
    float w;
}evec4;

typedef struct {
    float x;
    float y;
    float z;
}evec3;

typedef struct {
    float x;
    float y;
}evec2;

ermine_private void ComponentBaseMathImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_CMATH_H
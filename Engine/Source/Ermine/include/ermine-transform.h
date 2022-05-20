#ifndef ERMINE_TRANSFORM_H
#define ERMINE_TRANSFORM_H
#include <stdio.h>
#include <math.h>
#include "ermine-cmath.h"

typedef struct transform {
    evec2 position;
    evec2 scale;
    float angle;
    evec2 pivot;
    evec4 boundingbox;
}transform;

#endif // ERMINE_TRANSFORM_H
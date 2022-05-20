#ifndef ERMINE_MATH_H
#define ERMINE_MATH_H
#include <stdio.h>
#include "ermine.h"
#include "ermine-cmath.h"
#include "ermine-ctransform.h"
#include <math.h>

ermine_public evec2 ermine_math_vec2_add(evec2 a, evec2 b);

ermine_public evec2 ermine_math_vec2_sub(evec2 a, evec2 b);

ermine_public evec2 ermine_math_vec2_mul(evec2 a, evec2 b);

ermine_public evec2 ermine_math_vec2_scale(evec2 a, float b);

ermine_public evec2 ermine_math_vec2_normalize(evec2 a);

ermine_public evec2 ermine_math_vec2_lerp(evec2 a, evec2 b, float t);

ermine_public float ermine_math_vec2_distance(evec2 a, evec2 b);

ermine_public float ermine_math_vec2_length(evec2 a);

ermine_public float ermine_math_vec2_direction(evec2 a);

#endif // ERMINE_MATH_H
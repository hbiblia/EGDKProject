#include "ermine-math.h"
#include "ermine-gfx-renderer.h"

// -------------------
// MATRIX
// -------------------


// -------------------
// VECTOR 2
// -------------------
evec2 ermine_math_vec2_add(evec2 a, evec2 b)
{
    evec2 r = {a.x + b.x, a.y + b.y};
    return r;
}

evec2 ermine_math_vec2_sub(evec2 a, evec2 b)
{
    evec2 r = {a.x - b.x, a.y - b.y};
    return r;
}

evec2 ermine_math_vec2_mul(evec2 a, evec2 b)
{
    evec2 r = {a.x * b.x, a.y * b.y};
    return r;
}

evec2 ermine_math_vec2_scale(evec2 a, float b)
{
    evec2 r = {a.x * b, a.y * b};
    return r;
}

evec2 ermine_math_vec2_normalize(evec2 a)
{
    float len = ermine_math_vec2_length(a);
    return (len > 0 ? ermine_math_vec2_scale(a, 1.0f / len) : a);
}

evec2 ermine_math_vec2_lerp(evec2 a, evec2 b, float t)
{
    a.x = a.x + (b.x - a.x) * t;
    a.y = a.y + (b.y - a.y) * t;
    return a;
}

float ermine_math_vec2_distance(evec2 a, evec2 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return sqrtf(dx * dx + dy * dy);
}

float ermine_math_vec2_length(evec2 a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}

float ermine_math_vec2_direction(evec2 a)
{
    float rad = atan2(a.x, a.y);
    float deg = rad * 180.0f / M_PI;
    if (deg < 0)
        deg = 360.0f + deg;
    return deg;
}
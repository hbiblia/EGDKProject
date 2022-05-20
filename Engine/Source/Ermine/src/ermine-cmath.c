#include "ermine-cmath.h"

void ComponentBaseMathImport(ecs_world_t *world)
{
    ermine_component(evec2, {
        .label = "Vec2",
        .public = false,
        .property = {
            {.name = "x", .type = "float"},
            {.name = "y", .type = "float"}
        }
    });

    ermine_component(evec3, {
        .label = "Vec3",
        .public = false,
        .property = {
            {.name = "x", .type = "float"},
            {.name = "y", .type = "float"},
            {.name = "z", .type = "float"}
        }
    });

    ermine_component(evec4, {
        .label = "Vec4",
        .public = false,
        .property = {
            {.name = "x", .type = "float"},
            {.name = "y", .type = "float"},
            {.name = "z", .type = "float"},
            {.name = "w", .type = "float"}
        }
    });
}
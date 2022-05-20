#include "ermine-ctexture.h"

void ComponentTexture(ecs_world_t *world)
{
    ermine_component(etexture, {
        .label = "Texture",
        .public = false,
        .property = {
            {.name = "id", .type = "int"},
            {.name = "width", .type = "int"},
            {.name = "height", .type = "int"}
        }
    });
}
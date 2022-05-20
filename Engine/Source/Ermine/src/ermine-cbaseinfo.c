#include "ermine-cbaseinfo.h"

void ComponentBaseinfocomponentImport(ecs_world_t *world)
{
    ermine_component(baseinfocomponent, {
        .label = "Entity",
        .public = false,
        .property = {
            {.name = "name", .type = "string"}
        }
    });
}
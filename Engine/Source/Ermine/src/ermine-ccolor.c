#include "ermine-ccolor.h"

bool ermine_color_is_empty(ecolor color)
{
    bool empty = color.r == 0.0f && color.g == 0.0f && color.b == 0.0f && color.a == 0.0f;
    return empty;
}

ecolor ermine_color_random(void)
{
    float r = ((float)(rand() % 255) / 255);
    float g = ((float)(rand() % 255) / 255);
    float b = ((float)(rand() % 255) / 255);
    return (ecolor){r,g,b,1.0f};
}

void ComponentBaseColorImport(ecs_world_t *world)
{
    ermine_component(ecolor, {
        .label = "Color",
        .public = false,
        .property = {
            {.name = "r", .type = "float"},
            {.name = "g", .type = "float"},
            {.name = "b", .type = "float"},
            {.name = "a", .type = "float"},
        },
    });

    // ermine_component(ecolor, {
    //     "label":"Color",
    //     "property":[
    //         {"name":"r", "type":"float"},
    //         {"name":"g", "type":"float"},
    //         {"name":"b", "type":"float"},
    //         {"name":"a", "type":"float"}
    //     ]
    // });
}

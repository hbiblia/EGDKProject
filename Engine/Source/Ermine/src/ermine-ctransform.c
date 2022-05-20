#include "ermine-ctransform.h"
#include "ermine-math.h"

static SUpdateTransform(ecs_iter_t *it)
{
    etransform *child = ecs_term(it, etransform, 1);
    etransform *parent = ecs_term(it, etransform, 2);

    if(parent) {
        for (int i = 0; i < it->count; i++)
        {
            child[i].parent = &parent[i];
            // child -> parent <- parent
        }
    }
}

void ComponentBaseTransformImport(ecs_world_t *world)
{
    ermine_component(etransform, {
        .label = "Transform",
        .public = false,
        .property = {
            {.name = "position", .type = "evec2"},
            {.name = "scale", .type = "evec2"},
            {.name = "angle", .type = "float", .step = 1.0f},
            {.name = "pivot", .type = "evec2", .readonly = true},
        }
    });

    ECS_SYSTEM(world, SUpdateTransform, EcsOnValidate,
        [out] etransform,
        [in] etransform(parent|cascade));
}
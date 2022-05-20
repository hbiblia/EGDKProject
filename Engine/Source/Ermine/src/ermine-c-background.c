#include "ermine-c-background.h"
#include "ermine-ctransform.h"
#include "ermine-crenderer.h"
#include "ermine-gfx-renderer.h"

static void SrenderShapeRect(ecs_iter_t *it)
{
}

static void OAddComponent(ecs_iter_t *it)
{
}

void ComponentBackgroundTilingImport(ecs_world_t *world)
{
    ermine_component(ecBackgroundTiling, {
        .label = "BackgroundTiling",
        .public = true,
        .property = {
            {.name = "tilingPosition", .type = "evec2", .step = 1.0f},
            {.name = "tilingScale", .type = "evec2", .step = 1.0f},
            {.name = "tilingAngle", .type = "float", .step = 1.0f},
            {.name = "render", .type = "erenderer"},
        },
    });

    ECS_TAG(world, SystemOnRenderer);

    ECS_OBSERVER(world, OAddComponent, EcsOnAdd, eshaperect);

    // system
    // ermine_system_init(&(ecs_system_desc_t){
    //     .entity = {.add = {SystemOnRenderer}},
    //     .query.filter.terms = {
    //         {L("eshaperect")},
    //         {L("etransform")},
    //     },
    //     // .query.order_by = erenderer_order,
    //     // .query.order_by_component = L("eshaperect"),
    //     .callback = SrenderShapeRect,
    // });
}

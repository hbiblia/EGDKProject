#include "ermine-cshapes.h"
#include "ermine-ctransform.h"
#include "ermine-crenderer.h"
#include "ermine-gfx-renderer.h"

static void SrenderShapeRect(ecs_iter_t *it)
{
    eshaperect *shape = ecs_term(it, eshaperect, 1);
    etransform *trans = ecs_term(it, etransform, 2);

    for (int i = 0; i < it->count; i++)
    {
        eshaperect rect = shape[i];
        etransform tran = trans[i];

        ermine_r_shape_rectangle_draw(&(eshape_desc_t){
            .width = rect.width,
            .height = rect.height,
            .color = rect.color,
            .transform = tran,
        });
    }
}

static void OsetShapeRect(ecs_iter_t *it)
{
    eshaperect *shape = ecs_term(it, eshaperect, 1);

    for (int i = 0; i < it->count; i++)
    {
        shape[i].width = 100.0f;
        shape[i].height = 100.0f;
        shape[i].color = WHITE;
    }
}

void ComponentBaseShapesImport(ecs_world_t *world)
{
    ermine_component(eshaperect, {
        .label = "Rectangle",
        .public = true,
        .property = {
            {.name = "width", .type = "float", .step = 1.0f},
            {.name = "height", .type = "float", .step = 1.0f},
            {.name = "color", .type = "ecolor"},
            {.name = "render", .type = "erenderer"},
        },
    });

    ECS_TAG(world, SystemOnRenderer);

    ECS_OBSERVER(world, OsetShapeRect, EcsOnAdd, eshaperect);

    // system
    ermine_system_init(&(ecs_system_desc_t){
        .entity = {.add = {SystemOnRenderer}},
        .query.filter.terms = {
            {L("eshaperect")},
            {L("etransform")},
        },
        // .query.order_by = erenderer_order,
        // .query.order_by_component = L("eshaperect"),
        .callback = SrenderShapeRect,
    });
}

#include "ermine-crenderer.h"

int erenderer_order(ecs_entity_t entity_a, const void *component_1,
    ecs_entity_t entity_b, const void *component_2)
{
    (void)entity_a;
    (void)entity_b;

    erenderer *a = ECS_OFFSET(component_1, sizeof(erenderer)*3);
    erenderer *b = ECS_OFFSET(component_2, sizeof(erenderer)*3);
    return a->sortingOrder - b->sortingOrder;
}

void ComponentBaseRendererImport(ecs_world_t *world)
{
    ermine_component(erenderer, {0});

    // // system
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

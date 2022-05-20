#include "PlanePlayer.h"

static void fn_move()
{
    ermine_engine_t *api = ermine_get();

    for(int i = 0; i<it.count; i++)
    {
        if( api->event->keyboard->down() ){
            
        }
    }
}

static void ermine_component_init(void)
{
    ermine_engine_t *api = ermine_get();

    // create component
    api->ecs->component_init({
        .label = "ComponentPlanePlayer",
        .members = {
            {.name = "id", .type = "int"}
        }
    });

    // create system
    api->ecs->system_init({
        .callback = fn_move,
        .add = SysteOnUpdate,
        .filter = {
            {.name = "ComponentPlanePlayer"},
            {.name = "ComponentTransform"}
        }
    });
}

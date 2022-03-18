#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <eactor.h>

#include "component.transform.h"
#include "component.sprites.h"

static ecamera default_cam;

void init()
{
    default_cam = ecamera_make();

    actor e = actor_new("Entity11");
    actor_set(e, EcsPosition, {.x=10, .y=0, .z=10});
    actor_set(e, EcsScale, {.x=1, .y=1, .z=1});
    actor_set(e, EcsSprites, {.path = "background.png"});

    // actor e = actor_deserialize_data("");
    // char *data = actor_serialize_data(e);
    // printf("Data: %s\n", data);
}

void update()
{
    ebegin_mode(default_cam);
    {
        eactor_ecs_update();
    }
    eend_mode();
}

int main(int argc, char *argv[])
{
    printf("EGDKEditor v1.0-dev \n");

    ewindow_init((ewindow_desc){
        .title = "EGDKEditor - none",
        .width = 1024,
        .height = 768,
        .init_fn = init,
        .update_fn = update,
    });
}

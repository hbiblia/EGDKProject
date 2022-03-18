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

    eresource_assets_load("background.png");

    actor e = actor_new("Entity11");
    actor_set(e, EcsPosition, {0});
    actor_set(e, EcsScale, {0});
    actor_set(e, EcsRotation, {0});
    actor_set(e, EcsSprites, {.key = "background.png"});

    // actor e = actor_deserialize_data("");
    // char *data = actor_serialize_data(e);
    // printf("Data: %s\n", data);
}

void update()
{
    ebegin_mode(default_cam);
    {
        ecs_flecs_update();
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

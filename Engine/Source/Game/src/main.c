#include <stdio.h>
#include "ermine-core.h"
#include "ermine-window.h"
#include "ermine-resource.h"

#include "ermine-ecs.h"
#include "ermine-cshapes.h"
#include "ermine-ctransform.h"

typedef struct{
    float speed;
    int directionX;
}enemigoBrocoliComponent;

void Srebote(ecs_iter_t *it)
{
    enemigoBrocoliComponent *move = ecs_term(it, enemigoBrocoliComponent, 1);
    etransform *trans = ecs_term(it, etransform, 2);

    for (int i = 0; i < it->count; i++)
    {
        trans[i].position.x += move[i].speed * move[i].directionX * ermine_window_delta();

        if(trans[i].position.x <= -525|| trans[i].position.x >= 525){
            move[i].directionX *= -1;
        }
    }
}

int main(int argc, char *argv[])
{
    // ermine_init(argc, argv);

    // ermine_resource_project(argv[1]);

    // ermine_component(enemigoBrocoliComponent, {0});
    // ermine_system(Srebote, EcsOnUpdate, enemigoBrocoliComponent, etransform);

    // ecs_entity_t a1 = ermine_entity_new();
    // ermine_component_set(a1, eshaperect, {.width = 800.0f, .height = 25.0f, .color = WHITE});
    // ermine_component_set(a1, etransform, {.position = {0.0f,-500.0f}});

    // ecs_entity_t a2 = ermine_entity_new();
    // ermine_component_set(a2, eshaperect, {.width = 50.0f, .height = 100.0f, .color = RED});
    // ermine_component_set(a2, etransform, {.position = {600.0f,-375}});

    // for(int i = 1; i<3; i++){
    //     ecolor c1 = ermine_color_random();
    //     ecolor c2 = ermine_color_random();

    //     ecs_entity_t a3 = ermine_entity_new();
    //     ermine_component_set(a3, eshaperect, {.width = 50.0f, .height = 100.0f, .color = c1});
    //     ermine_component_set(a3, etransform, {.position = {-400.0f,-375}});
    //     ermine_component_set(a3, enemigoBrocoliComponent, {.speed = 105.0f * i, .directionX = -1});

    //     ecs_entity_t a4 = ermine_entity_new();
    //     ermine_component_set(a4, eshaperect, {.width = 50.0f, .height = 85.0f, .color = c2});
    //     ermine_component_set(a4, etransform, {.position = {0.0f,-390}});
    //     ermine_component_set(a4, enemigoBrocoliComponent, {.speed = 145.0f * i, .directionX = 1});
    // }
    
    // ermine_main();

    return 0;
}

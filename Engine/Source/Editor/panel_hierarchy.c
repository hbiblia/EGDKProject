#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <eactor.h>
#include <glib.h>

#include "component.transform.h"
#include "component.sprites.h"

static actor actor_selected = -1;
static actor_lengs = 0;

// static GPtrArray *actorsWorld_tmp;

void panel_hierarchy_init(void)
{
    // actorsWorld_tmp = g_ptr_array_new();
}

void panel_hierarchy_main(void)
{
    igSetNextWindowSize((ImVec2){100, 200}, 0);
    if (igBegin("Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        if (igButton("Agregar actor", (ImVec2){0, 0}))
        {
            actor e = actor_new(g_strdup_printf("Entity%d",actor_lengs));
            // actor_set(e, EcsSprites, {.key = "background.png"});
            actor_lengs++;
        }

        // Lista de actors
        // --------------------
        ecs_world_t *world = eactor_get_world();

        ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
            .filter.terms = {
                {.id = ecs_component_lookup("EcsPosition"), .inout = EcsIn}
            },
        });

        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it))
        {
            for (int i = 0; i < it.count; i++)
            {
                actor actor_now = it.entities[i];
                bool selected = (actor_selected == actor_now ? true : false);

                const char *name = ecs_get_name(world, actor_now);

                if(igSelectable_Bool(name, selected, ImGuiSelectableFlags_None, (ImVec2){0})){
                    actor_selected = actor_now;
                }
            }
        }
    }
    igEnd();
}

const char *hierarchy_get_selected_name(void)
{
    if(actor_selected == -1)return "None";
    ecs_world_t *world = eactor_get_world();
    return ecs_get_name(world, actor_selected);
}

actor hierarchy_get_selected(void)
{
    return actor_selected;
}

#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <flower.h>
#include <glib.h>

#include "component.transform.h"
#include "component.sprites.h"

// El actor que tenemos seleccionado
// desde este modulo.
static ecs_entity_t entity_selected = -1;


void panel_hierarchy_init(void)
{
}

void panel_hierarchy_main(void)
{
    igSetNextWindowSize((ImVec2){100, 200}, 0);
    if (igBegin("Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        igSameLine(0,0);
        if (igSmallButton("+"))
        {
            flower_entity_new("newEntity", true);
        }
        igSameLine(0,3.0f);
        if(igSmallButton("Duplicar")){
            if(entity_selected != -1){
                flower_entity_clone_new(entity_selected);
            }
        }

        igSameLine(0,3.0f);
        if(igSmallButton("Eliminar")){
            if(entity_selected != -1){
                flower_entity_remove(entity_selected);
            }
        }

        igSeparator();

        /*
         * Buscamos todas las entidades que tengan un TransformComponent
        */

        ecs_world_t *world = eactor_get_world();

        ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t) {
            .filter.terms = {
                {.id = flower_lookup("TransformComponent"), .inout = EcsIn}
            },
        });

        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it))
        {
            for (int i = 0; i < it.count; i++)
            {
                actor actor_now = it.entities[i];
                bool selected = (entity_selected == actor_now ? true : false);

                const char *name = ecs_get_name(world, actor_now);
                
                igPushID_Int(i);
                if(igSelectable_Bool(name, selected, ImGuiSelectableFlags_None, (ImVec2){0})) {
                    entity_selected = actor_now;
                }
                igPopID();
            }
        }

        ecs_query_fini(q);
    }
    igEnd();
}

const char *hierarchy_get_selected_name(void)
{
    if(entity_selected == -1)return "None";
    ecs_world_t *world = eactor_get_world();
    return ecs_get_name(world, entity_selected);
}

actor hierarchy_get_selected(void)
{
    return entity_selected;
}

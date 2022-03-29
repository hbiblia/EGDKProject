#include <stdio.h>
#include <stdbool.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <flower.h>

#include "component.info.h"

// La entidad que tenemos seleccionada.
static ecs_entity_t entiti_gselected = -1;

// La entidad principal
static ecs_entity_t entity_root = -1;

// temporal world hierarchy
static ecs_world_t *world;

// Realizamos la consulta para obtener los hijos de una entidad.
static ecs_iter_t hierarchy_get_children(ecs_entity_t entity);

// Hierarchy init
void panel_hierarchy_init(void)
{
    // temporal world hierarchy
    world = flower_get_world();

    // Creamos el ROOT que contendra todas las entidades del nivel.
    entiti_gselected = entity_root = flower_entity_new("Root", 0, false);
}

// Hierarchy render-update
void panel_hierarchy_main(void)
{
    igSetNextWindowSize((ImVec2){100, 200}, 0);
    if (igBegin("Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        igSameLine(0, 0);
        if (igSmallButton("+"))
        {
            flower_entity_new("newEntity", entiti_gselected, true);
        }

        // No puedes borrar el Root
        if (entity_root != entiti_gselected)
        {
            igSameLine(0, 3.0f);
            if (igSmallButton("Duplicar"))
            {
                if (entiti_gselected != -1)
                {
                    flower_entity_clone_new(entiti_gselected);
                }
            }
            igSameLine(0, 3.0f);
            if (igSmallButton("Eliminar"))
            {
                if (entiti_gselected != -1)
                {
                    flower_entity_remove(entiti_gselected);
                }
            }
        }

        igSeparator();

        /*
         * Buscamos todas las entidades que tengan un TransformComponent
         */
        // igScrollbar(0);
        hierarchy_draw_children(entity_root);
    }
    igEnd();
}

// Obtenemos el nombre de la entidad seleccionada.
const char *hierarchy_get_selected_name(void)
{
    if (entiti_gselected == -1)
        return "None";
    return flower_info_get_name(entiti_gselected);
}

// Obtenemos la entidad seleccionada.
ecs_entity_t hierarchy_get_selected(void)
{
    return entiti_gselected;
}

// Seleccionamos la entidad desde otro lugar del editor.
void hierarchy_set_selected(ecs_entity_t entity)
{
    entiti_gselected = entity;
}

// mantenemos el orden de las entidades segun su identificacion.
static int hierarchy_private_order_by(ecs_entity_t e1, const InfoComponent *ptr1, ecs_entity_t e2, const InfoComponent *ptr2)
{
    (void)e1;
    (void)e2;
    return ptr1->id - ptr2->id;
}

// Obtenemos los hijos de una entidad y lo mostramos.
// La idea es buscar los hijos de RootEntity -> entity -> e...
void hierarchy_draw_children(ecs_entity_t entity)
{
    // ---------------------------
    // Guardamos todas las entidades
    // de los hijos del entity-parent
    // ---------------------------
    ecs_entity_t *entities[100];
    int entities_count = 0;

    // ---------------------------
    // Una consulta para obtener
    // los hijos de entitys y ver
    // las entidades deshabilitadas
    // ---------------------------
    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {
            {.id = ecs_childof(entity)},
            {.id = EcsDisabled, .oper = EcsOptional},
        },
        // .order_by = hierarchy_private_order_by,
        // .order_by_component = flower_lookup("InfoComponent"),
    });
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            entities[entities_count] = it.entities[i];
            entities_count++;
        }
    }
    ecs_query_fini(q);

    // ---------------------------
    // nombre de la entidad
    // ---------------------------
    const char *name = flower_info_get_name(entity);

    // ---------------------------
    // si tenemos la entidad seleccionada
    // ---------------------------
    bool selected = (entiti_gselected == entity ? true : false);

    // ---------------------------
    // Los parent-entity se pueden
    // expander para mostrar el contenido,
    // los no-parent-entity no se pueden expandir.
    // ---------------------------
    bool bparent = entities_count > 0 ? true : false;
    if (!bparent)
    {
        // #no-parent-entity
        igPushID_Int(entity);
        if (igSelectable_Bool(name, selected, ImGuiSelectableFlags_None | ImGuiTreeNodeFlags_SpanAvailWidth, (ImVec2){0}))
        {
            entiti_gselected = entity;
        }
        igPopID();
    }
    else
    {
        // #parent-entity
        ImGuiTreeNodeFlags flags = selected ? ImGuiTreeNodeFlags_Selected : ImGuiSelectableFlags_None | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;

        // Si la entidad Root abrimos el TreeNode
        if (strcmp(name, "Root") == 0)
        {
            flags |= ImGuiTreeNodeFlags_DefaultOpen;
        }

        bool opened = igTreeNodeEx_Str(name, flags);

        if (igIsItemClicked(ImGuiMouseButton_Left))
        {
            entiti_gselected = entity;
        }
        if (opened)
        {
            for (int i = 0; i < entities_count; i++)
            {
                hierarchy_draw_children(entities[i]);
            }
            igTreePop();
        }
    }
}

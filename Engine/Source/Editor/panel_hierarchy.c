
#include <stdio.h>
#include <stdbool.h>

#define CIMGUI_IMPL
#include "ermine.h"
#include "ermine-flower.h"
#include "ermine-scene.h"
#include "editor-internal.h"

#define InfoComponent_EXPORTS
#include "InfoComponent.h"

// temporal world hierarchy
static ecs_world_t *world;

static ecs_iter_t hierarchy_get_children(ecs_entity_t entity);
static void hierarchy_draw_children(ecs_entity_t entity);
static int hierarchy_private_order_by(ecs_entity_t e1, const InfoComponent *ptr1, ecs_entity_t e2, const InfoComponent *ptr2);

// Hierarchy init
void panel_hierarchy_init(void)
{
    // temporal world hierarchy
    world = flower_get_world();
    hierarchy_set_selected(ermine_scene_get());
}

// Hierarchy render-update
void panel_hierarchy_main(void)
{
    igSetNextWindowSize((ImVec2){100, 200}, 0);
    if (igBegin("Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        ecs_entity_t entity = hierarchy_get_selected();
        
        igSameLine(0, 0);
        if (igSmallButton("+"))
        {
            flower_entity_new("newEntity", entity);
        }

        // No puedes borrar el Root
        if (ermine_scene_get() != entity && entity != -1)
        {
            igSameLine(0, 3.0f);
            if (igSmallButton("Duplicar"))
            {
                flower_entity_clone_new(entity);
            }
            igSameLine(0, 3.0f);
            if (igSmallButton("Eliminar"))
            {
                flower_entity_remove(entity);
            }
        }

        igSeparator();

        /*
         * Buscamos todas las entidades que tengan un TransformComponent
         */
        // igScrollbar(0);
        hierarchy_draw_children(ermine_scene_get());
    }
    igEnd();
}

// Obtenemos el nombre de la entidad seleccionada.
const char *hierarchy_get_selected_name(void)
{
    if (hierarchy_get_selected() == -1)
        return "None";
    return flower_info_get_name(hierarchy_get_selected());
}

// Obtenemos la entidad seleccionada.
ecs_entity_t hierarchy_get_selected(void)
{
    return editor_internal_get_entity();
}

// Seleccionamos la entidad desde otro lugar del editor.
void hierarchy_set_selected(ecs_entity_t entity)
{
    editor_internal_set_entity(entity);
}

// mantenemos el orden de las entidades segun su identificacion.
int hierarchy_private_order_by(ecs_entity_t e1, const InfoComponent *ptr1, ecs_entity_t e2, const InfoComponent *ptr2)
{
    (void)e1;
    (void)e2;
    return ptr1->id - ptr2->id;
}

// Obtenemos los hijos de una entidad y lo mostramos.
// La idea es buscar los hijos de RootEntity -> entity -> e...
void hierarchy_draw_children(ecs_entity_t entity)
{
    if(!ecs_is_valid(world, entity))return;

    // ---------------------------
    // Guardamos todas las entidades
    // de los hijos del entity-parent
    // ---------------------------
    ecs_entity_t *entities;
    int64_t entities_count = 0;

    // ---------------------------
    // Una consulta para obtener
    // los hijos de entitys y ver
    // las entidades deshabilitadas
    // ---------------------------
    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
        .filter.terms = {
            {.id = ecs_childof(entity)},
            {.id = EcsDisabled, .oper = EcsOptional},
            {.id = flower_lookup("InfoComponent")},
        },
        .order_by = hierarchy_private_order_by,
        .order_by_component = flower_lookup("InfoComponent"),
    });
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it))
    {
        entities = it.entities;
        entities_count = it.count;
    }
    ecs_query_fini(q);

    // ---------------------------
    // nombre de la entidad
    // ---------------------------
    const char *name = flower_info_get_name(entity);

    // ---------------------------
    // si tenemos la entidad seleccionada
    // ---------------------------
    bool selected = (editor_internal_get_entity() == entity ? true : false);

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
            hierarchy_set_selected(entity);
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
            hierarchy_set_selected(entity);
        }
        if (opened)
        {
            for (int i = 0; i < entities_count; i++)
            {
                ecs_entity_t list_e = (ecs_entity_t)entities[i];
                hierarchy_draw_children(list_e);
            }
            igTreePop();
        }
    }
}

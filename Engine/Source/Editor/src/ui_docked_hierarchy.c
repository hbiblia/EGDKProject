#include "ui_docked_hierarchy.h"
#include "ermine-ecs.h"
#include "editor_data.h"
#include "ermine-ctransform.h"
#include "ermine-cbaseinfo.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

static void hierarchy_draw_entity(ecs_entity_t e);
static void hierarchy_set_selected(ecs_entity_t e);

static ImGuiSelectableFlags flag_selectable = ImGuiSelectableFlags_None | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_FramePadding;

static ecs_entity_t cetransform = 0;

void ui_docked_hierarchy_init(void)
{
    editor_internal_set_selected_entity(ermine_entity_get_root());

    cetransform = L("etransform");
}

void ui_docked_hierarchy_render(void)
{
    igSetNextWindowSize((ImVec2){100, 200}, 0);
    if (igBegin("Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        igSameLine(0, 0);
        if (igSmallButton("+"))
        {
            ecs_entity_t t = ermine_entity_spawn();

            // si tenemos una entidad seleccionada sera padre de la nueva entidad.
            if (editor_internal_get_selected_entity() > 0)
            {
                ermine_entity_set_parent(editor_internal_get_selected_entity(), t);
            }
        }

        // Esto no deberia funcionar con el RootEntity
        igSameLine(0, 3.0f);
        if (igSmallButton("Duplicate"))
        {
            ecs_entity_t c = ermine_entity_clone(editor_internal_get_selected_entity());
        }

        igSameLine(0, 3.0f);

        if (igSmallButton("Delete"))
        {
            ermine_entity_delete(editor_internal_get_selected_entity());
            editor_internal_set_selected_entity(0);
        }

        igSeparator();

        // Obtenemos los hijos de las entidades Root.
        // Root es la entidad principal como si fuera una escena.
        hierarchy_draw_entity(ermine_entity_get_root());
    }
    igEnd();
}

int hierarchy_query_order_by(ecs_entity_t e1, const void *ptr1, ecs_entity_t e2, const void *ptr2)
{
    (void)e1;
    (void)e2;
    return e1 - e2;
}

void hierarchy_draw_entity(ecs_entity_t e)
{
    if (ermine_entity_is_valid(e))
    {
        const char *name = ermine_entity_get_name(e);

        bool bselected = (hierarchy_get_selected() == e ? true : false);

        bool bparent = ermine_entity_is_parent(e);
        if (bparent == false)
        {
            // #no-parent-entity
            igPushID_Int((int)e);
            if (igSelectable_Bool(name, bselected, flag_selectable, (ImVec2){0}))
            {
                hierarchy_set_selected(e);
            }
            igPopID();
        }
        else
        {
            // #parent-entity
            ImGuiTreeNodeFlags flags = flag_selectable;
            flags |= bselected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_OpenOnArrow;

            // Si la entidad Root abrimos el TreeNode
            if (strcmp(name, "Root") == 0)
            {
                flags |= ImGuiTreeNodeFlags_DefaultOpen;
            }

            bool bopened = igTreeNodeEx_Str(name, flags);

            // seleccionamos el nodo
            if (igIsItemClicked(ImGuiMouseButton_Left))
            {
                hierarchy_set_selected(e);
            }

            // abrimos un nodo
            if (bopened)
            {
                ecs_query_t *q = ermine_entity_query(&(ecs_query_desc_t){
                    .filter.terms = {
                        {.id = cetransform, .inout = EcsIn},
                        {.id = ermine_entity_get_parent(e)},
                        {.id = EcsDisabled, .oper = EcsOptional},
                    },
                    .order_by = hierarchy_query_order_by,
                });
                ecs_iter_t it = ermine_entity_query_iter(q);
                while (ermine_entity_query_next(&it))
                {
                    for (int i = 0; i < it.count; i++)
                    {
                        hierarchy_draw_entity(it.entities[i]);
                    }
                }
                ermine_entity_query_free(q);

                igTreePop();
            }
        }
    }
}

void hierarchy_set_selected(ecs_entity_t e)
{
    editor_internal_set_selected_entity(e);
}

ecs_entity_t hierarchy_get_selected(void)
{
    return editor_internal_get_selected_entity();
}

const char *hierarchy_get_selected_name(void)
{
    if (ermine_entity_is_valid(hierarchy_get_selected()) == false)
        return "None";

    return ermine_entity_get_name(hierarchy_get_selected());
}
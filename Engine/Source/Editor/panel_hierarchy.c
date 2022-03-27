#include <stdio.h>
#include <stdbool.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <flower.h>

// La entidad que tenemos seleccionada.
static ecs_entity_t entity_gselected = -1;

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
    entity_gselected = entity_root = flower_entity_new("Root", 0, false);
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
            flower_entity_new("newEntity", entity_gselected, true);
        }
        igSameLine(0, 3.0f);
        if (igSmallButton("Duplicar"))
        {
            if (entity_gselected != -1)
            {
                flower_entity_clone_new(entity_gselected);
            }
        }

        igSameLine(0, 3.0f);
        if (igSmallButton("Eliminar"))
        {
            if (entity_gselected != -1)
            {
                flower_entity_remove(entity_gselected);
            }
        }

        igSeparator();

        /*
         * Buscamos todas las entidades que tengan un TransformComponent
         */
        hierarchy_draw_children(entity_root);
    }
    igEnd();
}

// Obtenemos el nombre de la entidad seleccionada.
const char *hierarchy_get_selected_name(void)
{
    if (entity_gselected == -1)
        return "None";
    return ecs_get_name(world, entity_gselected);
}

// Obtenemos la entidad seleccionada.
ecs_entity_t hierarchy_get_selected(void)
{
    return entity_gselected;
}

// Seleccionamos la entidad desde otro lugar del editor.
void hierarchy_set_selected(ecs_entity_t entity)
{
    entity_gselected = entity;
}

// Obtenemos los hijos de una entidad y lo mostramos.
// La idea es buscar los hijos de RootEntity -> entity -> e...
void hierarchy_draw_children(ecs_entity_t entity)
{
    // Guardamos todas las entidades hijos del entity
    ecs_entity_t *entities[100];
    int entities_count = 0;

    // querys children entitys
    ecs_iter_t it = ecs_term_iter(world, &(ecs_term_t){.id = ecs_childof(entity)});
    while (ecs_term_next(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            entities[entities_count] = it.entities[i];
            entities_count++;
        }
    }

    // info entity
    const char *name = ecs_get_name(world, entity);

    // si tenemos la entidad seleccionada
    bool selected = (entity_gselected == entity ? true : false);

    // es parent o no, dime tu!
    bool bparent = entities_count > 0 ? true : false;
    if (!bparent)
    {
        if (igSelectable_Bool(name, selected, ImGuiSelectableFlags_None | ImGuiTreeNodeFlags_SpanAvailWidth, (ImVec2){0}))
        {
            entity_gselected = entity;
        }
    }
    else
    {
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
            entity_gselected = entity;
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

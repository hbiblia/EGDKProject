#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <ermine-flower.h>
#include "custom-imgui.h"

#include "editor-internal.h"

static bool first_selected = false;
static ecs_entity_t entiti_seleted = -1;
static ecs_world_t *world;

static float inspector_width = 0;

static void inspector_draw_component(const char *name, void *ptr, ecs_entity_t component);
static void inspector_process_component_data(void *ptr, ecs_entity_t component);

const ImGuiTreeNodeFlags flagsTreeNode = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

void panel_inspector_init(void)
{
    world = flower_get_world();
}

void panel_inspector_main(void)
{
    if (entiti_seleted != hierarchy_get_selected())
    {
        entiti_seleted = hierarchy_get_selected();
    }

    if (entiti_seleted != 1 && !ecs_is_valid(world, entiti_seleted))
    {
        entiti_seleted = -1;
    }

    // UI
    // ---------------------
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Inspector", false, ImGuiWindowFlags_NoMove))
    {
        inspector_width = igGetWindowWidth();

        if (entiti_seleted == -1)
        {
            igTextWrapped("Select anything to Inspect");
        }

        // List Components Properties
        // ---------------------
        // Description: Cargamos la lista de componentes de una
        // entidad seleccionada.
        if (entiti_seleted != -1)
        {
            ecs_type_t type = ecs_get_type(world, entiti_seleted);
            const ecs_id_t *ids = ecs_vector_first(type, ecs_id_t);
            int32_t count = ecs_vector_count(type);

            for (int i = 0; i < count; i++)
            {
                ecs_id_t id = ids[i];
                ecs_entity_t component = ecs_pair_second(world, id);
                char *name_component = ecs_get_name(world, component);
                const void *component_ptr = ecs_get_id(world, entiti_seleted, component);

                if (!component_ptr)
                    continue;

                // Component data
                // ---------------------
                inspector_draw_component(name_component, component_ptr, component);
            }
        }

        // Agregamos componentes nuevos
        // ---------------------
        igPushItemWidth(-1);
        {
            if (entiti_seleted != -1)
            {
                // Add components buttons
                // ---------------------
                float width = igGetWindowWidth();
                if (igButton("Add Component", (ImVec2){width, 0}))
                {
                    igOpenPopup_Str("AddComponent", 0);
                }

                // Add components menu-popups
                // ---------------------
                // igSetNextWindowSize((ImVec2){0, 300}, 0);
                if (igBeginPopup("AddComponent", ImGuiWindowFlags_AlwaysAutoResize))
                {
                    ecs_entity_t seleted = hierarchy_get_selected();

                    GSList *components = flower_component_get_list();
                    while ((char *)g_slist_nth_data(components, 0) != NULL)
                    {
                        char *name = g_strdup((char *)g_slist_nth_data(components, 0));
                        if (igMenuItem_Bool(name, "", false, true))
                        {
                            flower_set_component_empty(seleted, actor_get_lookup(name));
                        }
                        components = components->next;
                    }
                    igEndPopup();
                }
            }
            igPopItemWidth();
        }
    }
    igEnd();
}

void inspector_draw_component(const char *name, void *ptr, ecs_entity_t component)
{
    ImVec2 region = {0};
    igGetContentRegionAvail(&region);

    // igTreeNodeEx_Str
    igPushStyleVar_Vec2(ImGuiStyleVar_FramePadding, (ImVec2){4.0f, 4.0f});
    float lineHeight = igGetFontSize() + igGetStyle()->FramePadding.y * 2.0f;
    bool open = igTreeNodeEx_Str(name, flagsTreeNode);
    igPopStyleVar(1);

    // Borramos un componente diferente a los 2 por defecto.
    if (!(strcmp(name, "InfoComponent") == 0 || strcmp(name, "TransformComponent") == 0))
    {
        igSameLine(region.x - lineHeight * 0.5f, 0);
        if (igButton("-", (ImVec2){lineHeight, lineHeight}))
        {
            ecs_remove_id(flower_get_world(), hierarchy_get_selected(), component);
        }
    }
    // igTreeNodeEx_Str
    if (open)
    {
        inspector_process_component_data(ptr, component);
        igTreePop();
    }
}

void inspector_process_component_data(void *ptr, ecs_entity_t component)
{
    const EcsMetaTypeSerialized *ser = ecs_get(world, component, EcsMetaTypeSerialized);
    ecs_meta_type_op_t *ops = ecs_vector_first(ser->ops, ecs_meta_type_op_t);

    int32_t field_count = ecs_vector_count(ser->ops);
    for (int i = 0; i < field_count; i++)
    {
        ecs_meta_type_op_t *op = &ops[i];

        if (op->name)
        {
            ecs_entity_t element_type = op->type;
            const char *field_type_name = ecs_get_name(world, element_type);
            const char *field_label = op->name;
            void *value_ptr = (void *)ECS_OFFSET(ptr, op->offset);

            // DEBUG
            // printf("DEBUG INSPECTOR: %s -> %s\n", field_type_name, field_label);

            // Tipos de datos
            // ---------------------
            if (strcmp(field_type_name, "CFuntion") == 0)
            {
                imgui_labelPropBegin(field_label, i);
                bool bopened = igButton("", (ImVec2){0.0f, 0.0f});
                imgui_labelPropEnd();
                if (bopened)
                {
                    efuntion callback_fn = (efuntion)ECS_OFFSET(ptr, op->offset);
                    if (callback_fn)
                    {
                        callback_fn();
                    }
                }
            }
            else if (strcmp(field_type_name, "CVec2") == 0)
            {
                for (int u = 0; u < op->count; u++)
                {
                    const char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;

                    CVec2 *value = (CVec2 *)value_ptr;
                    float value_b[2] = {value[u].x, value[u].y};

                    imgui_labelPropBegin(name_field, i);
                    bool bopened = igDragFloat2(field_label, value_b, 0.01f, 0.0f, 0.0f, "%.2f", 0);
                    imgui_labelPropEnd();
                    if (bopened)
                    {
                        *value = evect2_new(value_b[0], value_b[1]);
                    }
                }
            }
            else if (strcmp(field_type_name, "CVec3") == 0)
            {
                for (int u = 0; u < op->count; u++)
                {
                    const char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;

                    CVec3 *value = (CVec3 *)value_ptr;
                    float value_b[3] = {value[u].x, value[u].y, value[u].z};

                    imgui_labelPropBegin(name_field, u + i);
                    bool bopened = igDragFloat3("", value_b, 0.01f, 0.0f, 0.0f, "%.2f", 0);
                    imgui_labelPropEnd();
                    if (bopened)
                    {
                        *value = evect3_new(value_b[0], value_b[1], value_b[2]);
                    }
                }
            }
            else if (strcmp(field_type_name, "CColor") == 0)
            {
                for (int u = 0; u < op->count; u++)
                {
                    const char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;
                    CColor *value_color = (CColor *)value_ptr;
                    float color_buffer[4] = {value_color[u].r, value_color[u].g, value_color[u].b, value_color->a};

                    imgui_labelPropBegin(name_field, u + i);
                    bool bopened = igColorEdit4("", color_buffer, ImGuiColorEditFlags_Float);
                    imgui_labelPropEnd();
                    if (bopened)
                    {
                        value_color[u] = ecolor_new(color_buffer[0], color_buffer[1], color_buffer[2], color_buffer[3]);
                    }
                }
            }
            else if (strcmp(field_type_name, "f32") == 0)
            {
                for (int u = 0; u < op->count; u++)
                {
                    const char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;
                    ecs_f32_t *value_f = (ecs_f32_t *)value_ptr;
                    imgui_labelPropBegin(name_field, u + i);
                    igInputFloat("", &value_f[u], 0.01f, 1.0f, "%.2f", 0);
                    imgui_labelPropEnd();
                }
            }
            else if (strcmp(field_type_name, "i8") == 0 || strcmp(field_type_name, "i32") == 0 || strcmp(field_type_name, "i64") == 0)
            {
                for (int u = 0; u < op->count; u++)
                {
                    char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;
                    int *value_i = (int *)value_ptr;
                    imgui_labelPropBegin(name_field, u + i);
                    igInputInt("", &value_i[u], 1, 2, 0);
                    imgui_labelPropEnd();
                }
            }
            else if (strcmp(field_type_name, "bool") == 0)
            {
                for (int u = 0; u < op->count; u++)
                {
                    const char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;
                    bool *value_b = (bool *)value_ptr;
                    imgui_labelPropBegin(name_field, u + i);
                    igCheckbox("", &value_b[u]);
                    imgui_labelPropEnd();
                }
            }
            else if (strcmp(field_type_name, "string") == 0)
            {
                for (int u = 0; u < op->count; u++)
                {
                    const char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;
                    ecs_string_t *fieldv = (ecs_string_t *)value_ptr;
                    char buffer[256] = "\0";
                    if (fieldv[u])
                        strncpy(buffer, fieldv[u], sizeof(buffer));

                    imgui_labelPropBegin(name_field, u + i);
                    if (igInputText("", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
                    {
                        *fieldv = g_strdup(buffer);
                    }
                    imgui_labelPropEnd();

                    // Recibinos datos del assets browser
                    if (igBeginDragDropTarget())
                    {
                        ImGuiPayload *drop = igAcceptDragDropPayload("ASSETS_RESOURCE_ITEM", 0);
                        if (drop)
                        {
                            *fieldv = g_strdup(eutil_file_get_name(drop->Data));
                        }
                        igEndDragDropTarget();
                    }
                }
            }
            else
            {
                for (int u = 0; u < op->count; u++)
                {
                    ecs_entity_t component_id = flower_lookup(field_type_name);
                    if (ecs_is_valid(world, component_id))
                    {
                        char *name_field = op->count > 1 ? STRDUPPF("%s%d", field_label, u) : field_label;
                        bool open = igTreeNodeEx_Str(name_field, flagsTreeNode);
                        if (open)
                        {
                            void *other_ptr = (op->count == 1 ? ptr : &ptr[u]);
                            inspector_process_component_data(other_ptr, flower_lookup(field_type_name));
                            igTreePop();
                        }
                    }
                }
            }

            i += (op->op_count - 1);
        }
    }
}

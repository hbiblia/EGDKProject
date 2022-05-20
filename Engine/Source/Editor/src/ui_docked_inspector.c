#include "ui_docked_inspector.h"

#include "ermine-ccolor.h"
#include "ermine-ctransform.h"
#include "ermine-ctexture.h"
#include "ermine-cmath.h"

#include "ermine-string.h"
#include "parson/parson.h"
#include <glib.h>

#include "editor_data.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"
#include "custom-imgui.h"

static void ui_inspector_draw_component(const char *name, const void *ptr, ecs_entity_t component);
static void inspector_process_component_data(const void *ptr, ecs_entity_t component, ecs_meta_property_desc_t *meta_data);

static void inspector_property_draw_string(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i);
static void inspector_property_draw_vect2(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i);
static void inspector_property_draw_float(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i);
static void inspector_property_draw_color(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i);

static const ImGuiTreeNodeFlags flags_treenode = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

static GList *components_list = NULL;

void ui_docked_inspector_init(void)
{
    components_list = ermine_component_list();
}

void ui_docked_inspector_render(void)
{
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Inspector", false, ImGuiWindowFlags_NoMove))
    {
        ecs_entity_t entity_selected = editor_internal_get_selected_entity();

        if (!ermine_entity_is_valid(entity_selected))
        {
            igTextWrapped("Select anything to Inspect");
        }
        else
        {
            // List Components Properties
            // ---------------------
            ecs_type_t type = ermine_entity_get_type(entity_selected);
            const ecs_id_t *ids = ecs_vector_first(type, ecs_id_t);
            int32_t count = ecs_vector_count(type);

            for (int i = 0; i < count; i++)
            {
                ecs_id_t id = ids[i];

                ecs_entity_t component_entity = ecs_pair_second(W, id);
                const void *component_ptr = ecs_get_id(W, entity_selected, component_entity);
                if (!component_ptr)
                    continue;

                const char *component_id = ecs_get_name(W, component_entity);

                ui_inspector_draw_component(component_id, component_ptr, component_entity);
            }

            // Agregamos componentes nuevos
            // ---------------------
            igPushItemWidth(-1);
            {
                float width = igGetWindowWidth();

                if (igButton("Add Component", (ImVec2){width, 0}))
                {
                    igOpenPopup_Str("AddComponent", 0);
                }

                if (igBeginPopup("AddComponent", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysUseWindowPadding))
                {
                    GList *l = NULL;
                    for (l = components_list; l != NULL; l = l->next)
                    {
                        ecs_meta_desc_t *meta_data = l->data;

                        if (meta_data->public == 1)
                        {
                            const char *id_comp = meta_data->id;
                            if (igMenuItem_Bool(ermine_strdup_printf("%sComponent", meta_data->label), "", false, true))
                            {
                                ermine_component_set_empty(entity_selected, id_comp);
                            }
                        }
                    }
                    // g_list_free(g_steal_pointer(&l));
                    igEndPopup();
                }
                igPopItemWidth();
            }
        }
    }
    igEnd();
}

void ui_inspector_draw_component(const char *name, const void *ptr, ecs_entity_t component)
{
    bool bopen = false;
    ecs_meta_desc_t *meta_data = ermine_component_meta_lookup(name);

    if (meta_data->label == NULL)
        return;

    const char *label_cmp = meta_data->label;

    ImVec2 region = {0};
    igGetContentRegionAvail(&region);

    igPushStyleVar_Vec2(ImGuiStyleVar_FramePadding, (ImVec2){4.0f, 4.0f});
    float lineHeight = igGetFontSize() + igGetStyle()->FramePadding.y * 2.0f;
    bopen = igTreeNodeEx_Str(label_cmp, flags_treenode);
    igPopStyleVar(1);

    // Borramos un componente diferente a los 2 por defecto.
    if (!(strcmp(name, "baseinfocomponent") == 0 || strcmp(name, "etransform") == 0))
    {
        igSameLine(region.x - lineHeight * 0.5f, 0);
        if (igButton("-", (ImVec2){lineHeight, lineHeight}))
        {
            ecs_entity_t selected_e = editor_internal_get_selected_entity();
            if (ermine_entity_is_valid(component) && ermine_entity_is_valid(selected_e))
            {
                ermine_component_remove(selected_e, name);
            }
        }
    }

    if (bopen)
    {
        inspector_process_component_data(ptr, component, meta_data->property);
        igTreePop();
    }
}

void inspector_process_component_data(const void *ptr, ecs_entity_t component, ecs_meta_property_desc_t meta_data[])
{
    for (int i = 0; i < META_MAX_PROPERTY_CACHE_SIZE; i++)
    {
        if (meta_data[i].name == NULL)
            break;

        const char *name = meta_data[i].name;
        const char *type = meta_data[i].type;
        const int barray = meta_data[i].barray;
        const bool readonly = meta_data[i].readonly;

        ecs_meta_property_desc_t prop = meta_data[i];

        if (readonly)
            continue;

        prop.step = (prop.step == 0 ? 0.1f : prop.step);

        int count_data = barray == 1 ? 0 : 1;
        for (int ai = 0; ai < count_data; ai++)
        {
            if (strcmp(type, "string") == 0)
            {
                inspector_property_draw_string(prop, ptr, i, ai);
            }
            else if (strcmp(type, "evec2") == 0)
            {
                inspector_property_draw_vect2(prop, ptr, i, ai);
            }
            else if (strcmp(type, "float") == 0)
            {
                inspector_property_draw_float(prop, ptr, i, ai);
            }
            else if (strcmp(type, "ecolor") == 0)
            {
                inspector_property_draw_color(prop, ptr, i, ai);
            }
        }
    }
}

void inspector_property_draw_string(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i)
{
    int uid = field_i + field_array_i;

    char buffer[256] = "\0";
    ecs_string_t *fieldv = (ecs_string_t *)(void *)ECS_ELEM(ptr, sizeof(ecs_string_t) * field_i, uid);

    if (fieldv[field_array_i])
        ermine_strncpy(buffer, fieldv[field_array_i], sizeof(buffer));

    imgui_labelPropBegin(prop.name, uid);
    if (igInputText("", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
    {
        fieldv[field_array_i] = ermine_strdup(buffer);
    }
    imgui_labelPropEnd();
}

void inspector_property_draw_vect2(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i)
{
    int uid = field_i + field_array_i;

    evec2 *fieldv = (evec2 *)(void *)ECS_ELEM(ptr, sizeof(evec2) * field_i, uid);
    float value[2] = {fieldv[field_array_i].x, fieldv[field_array_i].y};

    imgui_labelPropBegin(prop.name, uid);
    if (igDragFloat2("", value, prop.step, 0.0f, 0.0f, "%.2f", 0))
    {
        fieldv[field_array_i] = (evec2){value[0], value[1]};
    }
    imgui_labelPropEnd();
}

void inspector_property_draw_float(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i)
{
    int uid = field_i + field_array_i;

    ecs_f32_t *fieldv = (ecs_f32_t *)(void *)ECS_ELEM(ptr, sizeof(ecs_f32_t) * field_i, uid);

    imgui_labelPropBegin(prop.name, uid);
    igInputFloat("", &fieldv[field_array_i], prop.step, 1.0f, "%.2f", 0);
    imgui_labelPropEnd();
}

void inspector_property_draw_color(ecs_meta_property_desc_t prop, const void *ptr, int field_i, int field_array_i)
{
    int uid = field_i + field_array_i;

    ecolor *fieldv = (ecolor *)ECS_ELEM(ptr, sizeof(evec2) * 1, 1);

    float color[3] = {fieldv[field_array_i].r, fieldv[field_array_i].g, fieldv[field_array_i].b};

    imgui_labelPropBegin(prop.name, uid);
    if (igColorEdit3("", color, ImGuiColorEditFlags_Float))
    {
        fieldv[field_array_i] = (ecolor){color[0], color[1], color[2], 1.0f};
    }
    imgui_labelPropEnd();
}
#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <flower.h>

#include "editor.h"

static bool first_selected = false;
static ecs_entity_t entiti_seleted = -1;
static ecs_world_t *world;

static void inspector_draw_component(const char *name, void *ptr, ecs_entity_t component, ecs_id_t id);

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
                void *component_ptr = ecs_get_id(world, entiti_seleted, component);

                if (!component_ptr)
                    continue;

                // name_component = g_strdup(&name_component[1]);

                // Component data
                // ---------------------
                inspector_draw_component(name_component, component_ptr, component, id);
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
                if (igButton("Add Component", (ImVec2){0, 0}))
                {
                    igOpenPopup_Str("AddComponent", 0);
                }

                // Add components menu-popups
                // ---------------------
                if (igBeginPopup("AddComponent", 0))
                {
                    ecs_entity_t seleted = hierarchy_get_selected();

                    // EcsComponent

                    ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
                        .filter.terms = {
                            {.id = ecs_id(EcsComponent)},
                        },
                    });
                    ecs_iter_t it = ecs_query_iter(world, q);
                    while (ecs_query_next(&it))
                    {
                        for (int i = 0; i < it.count; i++)
                        {
                            char *name = ecs_get_name(world, it.entities[i]);
                            if (igMenuItem_Bool(name, "", false, true))
                            {
                                flower_set_component_empty(seleted, actor_get_lookup(name));
                            }
                        }
                    }
                    ecs_query_fini(q);
                    igEndPopup();
                }
            }
            igPopItemWidth();
        }
    }
    igEnd();
}

void inspector_draw_component(const char *name, void *ptr, ecs_entity_t component, ecs_id_t id)
{
    bool open = igTreeNodeEx_Str(name, ImGuiTreeNodeFlags_DefaultOpen);
    if (open)
    {
        // obtenemos los field de la entidad componente
        // que estan registrados en el meta.
        //  ---------------------
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

                // DEBUG
                // printf("DEBUG INSPECTOR: %s -> %s\n", field_type_name, field_label);

                // Tipos de datos
                // ---------------------
                if(strcmp(field_type_name, "AnimateAnimationDataComponent")==0)
                {
                    i += (op->op_count - 1);
                }else if(strcmp(field_type_name,"CFuntion")==0)
                {
                    if(igButton(field_label, (ImVec2){0.0f,0.0f})){
                        efuntion callback_fn = (efuntion)ECS_OFFSET(ptr, op->offset);
                        if(callback_fn){ callback_fn(); }
                    }
                    i += (op->op_count - 1);
                }else if (strcmp(field_type_name, "CVec2") == 0)
                {
                    CVec2 *value = (CVec2 *)ECS_OFFSET(ptr, op->offset);
                    float value_b[2] = {value->x, value->y};

                    if (igDragFloat2(field_label, value_b, 0.01f, 0.0f, 0.0f, "%.2f", 0))
                    {
                        *value = evect2_new(value_b[0], value_b[1]);
                    }
                    i += (op->op_count - 1);
                }
                else if (strcmp(field_type_name, "CVec3") == 0)
                {
                    CVec3 *value = (CVec3 *)ECS_OFFSET(ptr, op->offset);
                    float value_b[3] = {value->x, value->y, value->z};

                    if (igDragFloat3(field_label, value_b, 0.01f, 0.0f, 0.0f, "%.2f", 0))
                    {
                        *value = evect3_new(value_b[0], value_b[1], value_b[2]);
                    }
                    i += (op->op_count - 1);
                }
                else if (strcmp(field_type_name, "CColor") == 0)
                {
                    CColor *value_color = (CColor *)ECS_OFFSET(ptr, op->offset);
                    float color_buffer[4] = {value_color->r, value_color->g, value_color->b, value_color->a};

                    if (igColorEdit4(field_label, color_buffer, ImGuiColorEditFlags_Float))
                    {
                        *value_color = ecolor_new(color_buffer[0], color_buffer[1], color_buffer[2], color_buffer[3]);
                    }
                    i += (op->op_count - 1);
                }
                else if (strcmp(field_type_name, "f32") == 0)
                {
                    float *value_f = (float *)ECS_OFFSET(ptr, op->offset);
                    igDragFloat(field_label, value_f, 0.01f, 0.0f, 0.0f, "%.2f", 0);
                }
                else if (strcmp(field_type_name, "i8") == 0)
                {
                    uint8_t *value_f = (uint8_t *)ECS_OFFSET(ptr, op->offset);
                    igDragInt(field_label, value_f, 0.5f, 0, 0, "%d", 0);
                }
                else if (strcmp(field_type_name, "bool") == 0)
                {
                    bool *value_b = (bool *)ECS_OFFSET(ptr, op->offset);
                    igCheckbox(field_label, value_b);
                }
                else if (strcmp(field_type_name, "string") == 0)
                {
                    ecs_string_t *nbuffer = (ecs_string_t *)ECS_OFFSET(ptr, op->offset);

                    char buffer[256];
                    memset(buffer, 0, sizeof(buffer));
                    strncpy(buffer, *(ecs_string_t **)ECS_OFFSET(ptr, op->offset), sizeof(buffer));

                    if (igInputText(field_label, buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
                    {
                        *nbuffer = g_strdup(buffer);
                    }

                    if (igBeginDragDropTarget())
                    {
                        ImGuiPayload *drop = igAcceptDragDropPayload("ASSETS_RESOURCE_ITEM", 0);
                        if (drop)
                        {
                            *nbuffer = g_strdup(drop->Data);
                        }
                        igEndDragDropTarget();
                    }
                }else{
                    i += (op->op_count - 1);
                }
            }
        }
        igTreePop();
    }
}

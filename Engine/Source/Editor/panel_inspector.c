#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <eflecs.h>

#include "editor.h"
#include <glib.h>

#include "component.transform.h"
#include "component.sprites.h"

static bool first_selected = false;
static actor actor_seleted = -1;
static ecs_world_t *world;

static void inspector_draw_component(const char *name, void *ptr, ecs_entity_t component, ecs_id_t id);

void panel_inspector_init(void)
{
    world = eactor_get_world();
}

void panel_inspector_main(void)
{
    if (actor_seleted != hierarchy_get_selected())
    {
        actor_seleted = hierarchy_get_selected();
        if (actor_seleted != -1)
        {
            // ecs_world_t *world = eactor_get_world();
            // printf("Selected: %u\n", actor_seleted);

            char *data = actor_serialize_data(actor_seleted);
            // printf("Data: %s\n", data);

            // jroot = json_parse_string(data);

            // ecs_query_t *q = ecs_query_init(world, &(ecs_query_desc_t){
            //     .filter.terms = {
            //         {.id = ecs_id(EcsComponent)}
            //     },
            // });

            // ecs_iter_t it = ecs_query_iter(world, q);
            // while (ecs_query_next(&it)) {
            //     for (int i = 0; i < it.count; i ++) {
            //         printf("Components: %s\n", ecs_get_name(world, it.entities[i]));
            //     }
            // }
        }
    }

    // UI
    // ---------------------
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Inspector", false, ImGuiWindowFlags_NoMove))
    {
        if (actor_seleted != -1)
        {
            // Tenemos el nombre de la entida seleccionada y podemos cambiarlo.
            // Por seguridad no permitimos el cambio de la entidad a 0.
            char buffer[256];
            char *ecs_name = ecs_get_name(world, actor_seleted);
            strcpy(buffer, ecs_name);
            if (igInputText("Name", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
            {
                if (strlen(buffer) > 0)
                {
                    ecs_set_name(world, actor_seleted, buffer);
                }
            }
            igSeparator();
            igSameLine(0, 0);
        }

        // List Components Properties
        // ---------------------
        // Description: Cargamos la lista de componentes de una
        // entidad seleccionada.
        if (actor_seleted != -1)
        {
            ecs_type_t type = ecs_get_type(world, actor_seleted);
            const ecs_id_t *ids = ecs_vector_first(type, ecs_id_t);
            int32_t count = ecs_vector_count(type);

            for (int i = 0; i < count; i++)
            {
                ecs_id_t id = ids[i];
                ecs_entity_t component = ecs_pair_second(world, id);
                char *name_component = ecs_get_name(world, component);
                void *component_ptr = ecs_get_id(world, actor_seleted, component);

                if (!component_ptr)
                    continue;

                name_component = g_strdup(&name_component[1]);

                // Component data
                // ---------------------
                inspector_draw_component(name_component, component_ptr, component, id);
            }
        }

        // Agregamos componentes nuevos
        // ---------------------
        igPushItemWidth(-1);
        {
            if (actor_seleted != -1)
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
                    actor seleted = hierarchy_get_selected();

                    if (igMenuItem_Bool("Camera", "", false, true))
                    {
                    }
                    if (igMenuItem_Bool("SpriteRender", "", false, true))
                    {
                        actor_set_empty(seleted, actor_get_lookup("CSprites"));
                    }
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
    bool open = igTreeNodeEx_Str(name, 0);
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
                // printf("DEBUG INSPECTOR: %s\n", field_label);

                // Tipos de datos
                // ---------------------

                if (strcmp(field_type_name, "CVec2") == 0)
                {
                    CVec2 *value = (CVec2 *)ECS_OFFSET(ptr, op->offset);
                    float value_b[2] = {value->x, value->y};

                    if (igDragFloat2(field_label, value_b, 0.1f, 0.0f, 0.0f, "%.2f", 0))
                    {
                        *value = evect2_new(value_b[0], value_b[1]);
                    }
                    i += op->op_count;
                }
                else if (strcmp(field_type_name, "CVec3") == 0)
                {
                    CVec3 *value = (CVec3 *)ECS_OFFSET(ptr, op->offset);
                    float value_b[3] = {value->x, value->y, value->z};

                    if (igDragFloat3(field_label, value_b, 0.1f, 0.0f, 0.0f, "%.2f", 0))
                    {
                        *value = evect3_new(value_b[0], value_b[1], value_b[2]);
                    }
                    i += op->op_count;
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
                    igDragFloat(field_label, value_f, 0.1f, 0.0f, 0.0f, "%.2f", 0);
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
                        ImGuiPayload *drop = igAcceptDragDropPayload("ASSETS_ITEM", 0);
                        if (drop)
                        {
                            *nbuffer = g_strdup(drop->Data);
                        }
                        igEndDragDropTarget();
                    }
                }
            }
        }
        igTreePop();
    }
}

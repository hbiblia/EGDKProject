#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <eactor.h>

#include "editor.h"
#include <glib.h>
#include "parson/parson.h"

#include "component.transform.h"
#include "component.sprites.h"

static bool first_selected = false;
static actor actor_seleted = -1;
static ecs_world_t *world;

// static JSON_Value *jroot;
// static JSON_Array *jarray;
// static JSON_Object *jobject;

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
        const char *name = hierarchy_get_selected_name();
        igText(g_strdup_printf("Actor Selected: %s", name));

        igSeparator();
        igSameLine(0, -1);
        igSeparator();
        igPushItemWidth(-1);

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
                    actor_set(seleted, EcsSprites, {.key = "background.png"});
                }
                igEndPopup();
            }
            igPopItemWidth();
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
                const char *name_component = ecs_get_name(world, component);
                void *component_ptr = ecs_get_id(world, actor_seleted, component);

                if (!component_ptr)continue;

                // Component data
                // ---------------------
                inspector_draw_component(name_component, component_ptr, component, id);
            }
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

                if (strcmp(field_type_name, "Vect2") == 0)
                {
                    EcsVect2 *value = (EcsVect2 *)ECS_OFFSET(ptr, op->offset);
                    float value_b[2] = {value->x, value->y};

                    if (igDragFloat2(field_label, value_b, 0.1f, 0.0f, 0.0f, "%.2f", 0))
                    {
                        *value = evect2_new(value_b[0], value_b[1]);
                    }
                    i += op->op_count;
                }
                else if (strcmp(field_type_name, "Vect3") == 0)
                {
                    EcsVect3 *value = (EcsVect3 *)ECS_OFFSET(ptr, op->offset);
                    float value_b[3] = {value->x, value->y, value->z};

                    if (igDragFloat3(field_label, value_b, 0.1f, 0.0f, 0.0f, "%.2f", 0))
                    {
                        *value = evect3_new(value_b[0], value_b[1], value_b[2]);
                    }
                    i += op->op_count;
                }
                else if (strcmp(field_type_name, "Color") == 0)
                {
                    EcsColor *value_color = (EcsColor *)ECS_OFFSET(ptr, op->offset);
                    float color_buffer[4] = {value_color->r, value_color->g, value_color->b, value_color->a};

                    if (igColorEdit4(field_label, color_buffer, ImGuiColorEditFlags_Float))
                    {
                        *value_color = ecolor_new(color_buffer[0], color_buffer[1], color_buffer[2], color_buffer[3]);
                    }
                    i += (op->op_count-1);
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
                    char buffer[100];
                    strcpy(buffer, *(char **)ECS_OFFSET(ptr, op->offset));

                    if (igInputText(field_label, buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
                    {
                        // char *nbuffer = (char *)ECS_OFFSET(ptr, op->offset);
                        // nbuffer = g_strdup(buffer);
                    }
                }
            }
        }
        igTreePop();
    }
}

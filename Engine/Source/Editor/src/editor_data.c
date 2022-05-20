#include "editor_data.h"
#include "ermine-ecs.h"

static ecs_entity_t selecteds;

ecs_entity_t editor_internal_get_selected_entity(void)
{
    return selecteds;
}

void editor_internal_set_selected_entity(ecs_entity_t e)
{
    selecteds = e;
}

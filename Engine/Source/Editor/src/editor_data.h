#ifndef EDITOR_DATA_H
#define EDITOR_DATA_H
#include <stdio.h>
#include "ermine-ecs.h"

ecs_entity_t editor_internal_get_selected_entity(void);

void editor_internal_set_selected_entity(ecs_entity_t e);

#endif // EDITOR_DATA_H
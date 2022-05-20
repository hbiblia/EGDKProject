#ifndef UI_DOCKED_HIERARCHY_H
#define UI_DOCKED_HIERARCHY_H
#include <stdio.h>
#include "ermine-ecs.h"

void ui_docked_hierarchy_init(void);
void ui_docked_hierarchy_render(void);
ecs_entity_t hierarchy_get_selected(void);
const char *hierarchy_get_selected_name(void);

#endif // UI_DOCKED_HIERARCHY_H
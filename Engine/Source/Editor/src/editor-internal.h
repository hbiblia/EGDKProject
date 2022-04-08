#ifndef EDITOR_MAIN_H
#define EDITOR_MAIN_H
#include <stdio.h>
#include <stdbool.h>

// -------------
// VIEWPORT
// -------------

void panel_viewport_init(void);

void panel_viewport_main(void);

// -------------
// INSPECTOR
// -------------

void panel_inspector_init(void);

void panel_inspector_main(void);

// -------------
// HIERARCHY
// -------------

void panel_hierarchy_init(void);

void panel_hierarchy_main(void);

const char *hierarchy_get_selected_name(void);

ecs_entity_t hierarchy_get_selected(void);

void hierarchy_set_selected(ecs_entity_t selected);

// -------------
// ASSETS
// -------------

void panel_assets_init(void);

void panel_assets_main(void);

// -------------
// FUNC DEL EDITOR
// -------------

void editor_internal_resource_default(void);

void editor_internal_open_scene(const char *name);

void editor_internal_set_entity(ecs_entity_t entity);

ecs_entity_t editor_internal_get_entity(void);

#endif // EDITOR_MAIN_H

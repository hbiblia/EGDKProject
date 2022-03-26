#ifndef EDITOR_MAIN_H
#define EDITOR_MAIN_H
#include <stdio.h>

// VIEWPORT
// -------------
void panel_viewport_init(void);
void panel_viewport_main(void);

// INSPECTOR
// -------------
void panel_inspector_init(void);
void panel_inspector_main(void);

// HIERARCHY
// -------------
void panel_hierarchy_init(void);
void panel_hierarchy_main(void);
actor hierarchy_get_selected(void);
const char *hierarchy_get_selected_name(void);

// ASSETS
// -------------
void panel_assets_init(void);
void panel_assets_main(void);

// FUNC DEL EDITOR
// -------------

/*
 * Guardamos la escena y si no tenemos una abierta
 * la creamos con los nuevos datos.
 *
 */

void editor_internal_level_save(void);

/*
 * Cargamos un level existente.
 *
 */

void editor_internal_level_open(const char *filename);

#endif // EDITOR_MAIN_H

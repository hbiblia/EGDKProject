#ifndef EDITOR_MAIN_H
#define EDITOR_MAIN_H
#include <stdio.h>
#include <stdbool.h>

// -------------
// VIEWPORT
// -------------

/*
 * Viewport init.
 *
 */

void panel_viewport_init(void);

/*
 * Viewport render-update.
 *
 */

void panel_viewport_main(void);

// -------------
// INSPECTOR
// -------------

/*
 * Inspector init.
 *
 */

void panel_inspector_init(void);

/*
 * Inspector render-update.
 *
 */

void panel_inspector_main(void);

// -------------
// HIERARCHY
// -------------

/*
 * Hierarchy init.
 *
 */

void panel_hierarchy_init(void);

/*
 * Hierarchy render-update.
 *
 */

void panel_hierarchy_main(void);

/*
 * Obtenemos el nombre de la entidad seleccionada.
 *
 */

const char *hierarchy_get_selected_name(void);

/*
 * Obtenemos la entidad seleccionada.
 *
 */

ecs_entity_t hierarchy_get_selected(void);

/*
 * Seleccionamos la entidad desde otro lugar del editor.
 *
 */

void hierarchy_set_selected(ecs_entity_t selected);

// -------------
// ASSETS
// -------------

/*
 * Assets init.
 *
 */

void panel_assets_init(void);

/*
 * Assets render-update.
 *
 */

void panel_assets_main(void);

// -------------
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

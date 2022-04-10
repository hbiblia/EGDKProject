#include "ermine.h"
#include "ermine-flower.h"
#include "ermine-scene.h"
#include "ermine-resource.h"
#include "ermine-util.h"

static ecs_entity_t entiti_gselected = -1;

void editor_internal_set_entity(ecs_entity_t entity)
{
    entiti_gselected = entity;
}

ecs_entity_t editor_internal_get_entity(void)
{
    return entiti_gselected;
}

void editor_internal_resource_default(void)
{
    printf("INFO: Load default resource\n");
    // Cargamos resource del engine
    ermine_resource_load(PATH_BUILD("texture", "folder.png"), "resource::iconFolder", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "scene.png"), "resource::iconScene", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "prefab.png"), "resource::iconPrefab", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "component.png"), "resource::iconComponent", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "system.png"), "resource::iconSystem", RESOURCE_PATH_ENGINE);
}

void editor_internal_open_scene(const char *name)
{
    const char *name_project = ermine_resource_get_path(RESOURCE_NAME_PROJECT);
    ewindow_set_title(STRDUPPF("%s - %s",name_project, name));
    
    ermine_scene_open(name);

    editor_internal_set_entity(ermine_scene_get());
}

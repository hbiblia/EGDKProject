#include "ermine.h"
#include "ermine-flower.h"

/*
 * Cargamos cosas basicas del editor
 * que pueden estar en resource.
 *
 */

void editor_internal_resource_default(void)
{
    // Cargamos resource del engine
    ermine_resource_load(PATH_BUILD("texture", "folder.png"), "resource::iconFolder", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "scene.png"), "resource::iconScene", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "prefab.png"), "resource::iconPrefab", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "component.png"), "resource::iconComponent", RESOURCE_PATH_ENGINE);
    ermine_resource_load(PATH_BUILD("texture", "system.png"), "resource::iconSystem", RESOURCE_PATH_ENGINE);
}

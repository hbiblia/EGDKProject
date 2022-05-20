#ifndef ERMINE_RESOURCE_H
#define ERMINE_RESOURCE_H
#include <stdio.h>
#include <stdlib.h>
#include "parson/parson.h"
#include "ermine.h"

enum
{
    RESOURCE_PATH_PROJECT,
    RESOURCE_PATH,
    RESOURCE_PATH_ENGINE,
    RESOURCE_PROJECT_NAME,
    RESOURCE_PROJECT,
    RESOURCE_ASSETS,
    RESOURCE_LAST
};

enum
{
    RESOURCE_OPROJECT,
    RESOURCE_OASSETS,
    RESOURCE_OBJ_LAST
};


// Para cargar los path de un proyecto.
ermine_public void ermine_resource_project(const char *project_path_str);

// Para cargar el path del engine.
ermine_private void ermine_resource_init(const char *path_str);
ermine_private const char *ermine_resource_get_path(int id);
ermine_private JSON_Value *ermine_resource_get_object(int id);

ermine_private void ermine_resource_close(void);

#endif
#ifndef ERMINE_RESOURCE_H
#define ERMINE_RESOURCE_H

#include "ermine.h"
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

ermine_public void ermine_resource_init(const char *path_project);

ermine_public void ermine_resource_close(void);

ermine_public void ermine_resource_load(const char *filename, const char *key,  int path_type);

ermine_public const char *ermine_resource_get_path(int path_id);

ermine_public etexture ermine_resource_get_texture(const char *key);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_RESOURCE_H
#ifndef ERMINE_RESOURCE_H
#define ERMINE_RESOURCE_H
#include "ermine.h"

void ermine_resource_init(const char *path_project);

void ermine_resource_close(void);

void ermine_resource_load(const char *filename, const char *key,  int path_type);

const char *ermine_resource_get_path(int path_id);

etexture ermine_resource_get_texture(const char *key);

#endif // ERMINE_RESOURCE_H
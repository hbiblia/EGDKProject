#ifndef ERMINE_ASSETS_H
#define ERMINE_ASSETS_H
#include "parson/parson.h"

// -- --
void ermine_assets_manager_init(const char *file_name);

JSON_Array *ermine_assetsm_get_roots(void);

const char *ermine_assetsm_get_file_path(void);

// -- --
JSON_Object *ermine_assetsm_find_by(const char *id, const char *value);

JSON_Object *ermine_assetsm_find_by_custom(const char *id, const char *value, JSON_Array *r);

JSON_Value *ermine_assetsm_new_object(const char *name, const char *type, const char *ext);

JSON_Status ermine_assetsm_save_file(void);

// resource assets
void ermine_assetsm_resource_load_content_custom(JSON_Array *roots);

void ermine_assetsm_resource_load_content(void);

#endif // ERMINE_ASSETS_H
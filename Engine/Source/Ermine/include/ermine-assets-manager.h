#ifndef ERMINE_ASSETS_H
#define ERMINE_ASSETS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine-config.h"
#include "parson/parson.h"


// -- --
ermine_public void ermine_assets_manager_init(const char *file_name);

ermine_public JSON_Array *ermine_assetsm_get_roots(void);

ermine_public const char *ermine_assetsm_get_file_path(void);

// -- --
ermine_public JSON_Object *ermine_assetsm_find_by(const char *id, const char *value);

ermine_public JSON_Object *ermine_assetsm_find_by_custom(const char *id, const char *value, JSON_Array *r);

ermine_public JSON_Value *ermine_assetsm_new_object(const char *name, const char *type, const char *ext);

ermine_public JSON_Status ermine_assetsm_save_file(void);

// resource assets
ermine_public void ermine_assetsm_resource_load_content_custom(JSON_Array *roots);

ermine_public void ermine_assetsm_resource_load_content(void);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_ASSETS_H
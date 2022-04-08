#ifndef ERMINE_SCENE_H
#define ERMINE_SCENE_H
#include "ermine-config.h"
#include "ermine-flower.h"

#define ROOT_SCENE_NAME "Root"

ermine_public void ermine_scene_init(void);

ermine_public ecs_entity_t ermine_scene_get(void);

ermine_public void ermine_scene_save(void);

ermine_public void ermine_scene_new(const char *name);

ermine_public void ermine_scene_open(const char *name);

ermine_public bool ermine_scene_is_open(void);

ermine_public bool ermine_scene_is_save(void);

ermine_public void ermine_scene_set_save(bool bSave);

ermine_public const char *ermine_scene_active_get_name(void);

#endif // ERMINE_SCENE_H
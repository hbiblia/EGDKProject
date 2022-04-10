#include "ermine-scene.h"
#include "ermine-assets-manager.h"
#include "ermine-resource.h"
#include "ermine-util.h"

static bool scenem_openscene = false;
static bool scenem_savescene = false;
static char *scenem_open_filename = NULL;
static char *scenem_name = NULL;

// Una escena es una coleccion de entidades
// donde la principal es la ROOT.
static ecs_entity_t RootEntity;

// Funcs

static void ermine_scene_set_open(bool bOpen)
{
    scenem_openscene = bOpen;
}

void ermine_scene_init(void)
{
    flower_reset_entity_world_len();

    if (ecs_is_valid(flower_get_world(), RootEntity))
        flower_entity_remove(RootEntity);

    RootEntity = flower_entity_new_custom(ROOT_SCENE_NAME, 0, false, true);
}

ecs_entity_t ermine_scene_get(void)
{
    return RootEntity;
}

void ermine_scene_clear(void)
{
}

void ermine_scene_save(void)
{
    if (ermine_scene_is_open())
    {
        ecs_entity_t root = flower_lookup("Root");
        JSON_Value *value = flower_internal_serialize(root, NULL);
        JSON_Status status = json_serialize_to_file(value, scenem_open_filename);

        if (status == JSONSuccess)
        {
            ermine_scene_set_save(true);
            printf("INFO: Save scene [%s]\n", scenem_name);
        }
        else
        {
            printf("INFO: Error save scene [%s]\n", scenem_name);
        }
    }
    else
    {
        ermine_scene_set_save(false);
    }
}

void ermine_scene_open(const char *name)
{
    JSON_Object *folder_scenes = ermine_assetsm_find_by("id", "3");
    JSON_Array *folder = json_object_get_array(folder_scenes, "children");
    JSON_Object *scene = ermine_assetsm_find_by_custom("name", name, folder);

    char *name_file = STRDUPPF("r%.0f.scene", json_object_get_number(scene, "id"));
    scenem_open_filename = PATH_BUILD(ermine_resource_get_path(RESOURCE_PATH), name_file);

    scenem_name = STRDUP(name);

    ermine_scene_set_open(true);
    JSON_Value *value = json_parse_file(scenem_open_filename);

    // ermine_scene_init();

    flower_internal_deserialize(value);

    printf("INFO: Open scene [%s]\n", name);
}

bool ermine_scene_is_open(void)
{
    return scenem_openscene;
}

bool ermine_scene_is_save(void)
{
    return scenem_savescene;
}

void ermine_scene_set_save(bool bSave)
{
    scenem_savescene = bSave;
}

const char *ermine_scene_active_get_name(void)
{
    return scenem_name ? scenem_name : "None";
}

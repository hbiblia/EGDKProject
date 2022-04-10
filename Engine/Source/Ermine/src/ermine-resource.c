
#include "ermine.h"
#include "ermine-flower.h"
#include "ermine-assets-manager.h"
#include "ermine-util.h"
#include "ermine-hash.h"
#include "ermine-resource.h"

#define MAX_RESOURCE_FILE 1000

static char *path_resource[RESOURCE_LAST];

static struct hashtable *hash_table;

static int texture_id_resource = 0;

static etexture texture_resource_data[MAX_RESOURCE_FILE];

// funcs

void ermine_resource_init(const char *path_project)
{
    hash_table = hash_table_new();

    // path resource del proyecto.
    path_resource[RESOURCE_PATH_PROJECT] = PATH_BUILD(path_project);
    path_resource[RESOURCE_PATH] = PATH_BUILD(path_project, "resource");
    path_resource[RESOURCE_PATH_ENGINE] = PATH_BUILD(ermine_path_get_current(), "resource");

    path_resource[RESOURCE_NAME_PROJECT] = STRDUP(ermine_file_get_name(path_project));

    // assets.json
    ermine_assets_manager_init(PATH_BUILD(path_resource[RESOURCE_PATH], "assets.json"));

    printf("INFO: Resource path: [%s]\n", path_resource[RESOURCE_PATH]);
    printf("INFO: Resource path engine [%s]\n", path_resource[RESOURCE_PATH_ENGINE]);
}

void ermine_resource_close(void)
{
    hash_table_destroy(hash_table);
}

const char *ermine_resource_get_path(int path_id)
{
    return path_resource[path_id];
}

void ermine_resource_load(const char *filename, const char *key,  int path_type)
{
    int id_temporal = -1;

    char *file_name_path = PATH_BUILD(path_resource[path_type], filename);

    if (ermine_file_is_extension(filename, ".png") || ermine_file_is_extension(filename, ".jpg"))
    {
        id_temporal = texture_id_resource;
        texture_resource_data[texture_id_resource] = etexture_load(file_name_path);
        texture_id_resource += 1;
        printf("LOAD: Resource load texture [%s]\n", filename);
    }

    if (id_temporal != -1)
    {
        hash_table_insert(hash_table, key, id_temporal);
    }
}

etexture ermine_resource_get_texture(const char *key)
{
    int id = hash_table_lookup(hash_table, key);
    return texture_resource_data[id];
}

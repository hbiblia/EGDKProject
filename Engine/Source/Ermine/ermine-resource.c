
#include "ermine.h"
#include "ermine-flower.h"
#include "ermine-assets-manager.h"

#define MAX_RESOURCE_FILE 1000

/*
 * Resource: Guardamos el path del
 * resource del proyecto.
 */

static char *path_resource[RESOURCE_LAST];

/*
 * Resource: Administra los archivos
 * que se utilizan en el motor.
 */

static GHashTable *hash_table;

static int texture_id_resource = 0;
static etexture texture_resource_data[MAX_RESOURCE_FILE];

void ermine_resource_init(const char *path_project)
{
    hash_table = g_hash_table_new(g_str_hash, g_str_equal);

    // path resource del proyecto.
    path_resource[RESOURCE_PATH_PROJECT] = PATH_BUILD(path_project);
    path_resource[RESOURCE_PATH] = PATH_BUILD(path_project, "resource");
    path_resource[RESOURCE_PATH_ENGINE] = PATH_BUILD(g_get_current_dir(), "resource");

    // assets.json
    ermine_assets_manager_init(PATH_BUILD(path_resource[RESOURCE_PATH], "assets.json"));

    printf("INFO: Resource path: [%s]\n", path_resource[RESOURCE_PATH]);
    printf("INFO: Resource path engine [%s]\n", path_resource[RESOURCE_PATH_ENGINE]);
}

void ermine_resource_close(void)
{
    g_hash_table_destroy(hash_table);
}

const char *ermine_resource_get_path(int path_id)
{
    return path_resource[path_id];
}

void ermine_resource_load(const char *filename, const char *key,  int path_type)
{
    int id_temporal = -1;

    char *file_name_path = PATH_BUILD(path_resource[path_type], filename);

    if (eutil_isfile_extension(filename, ".png") || eutil_isfile_extension(filename, ".jpg"))
    {
        id_temporal = texture_id_resource;
        texture_resource_data[texture_id_resource] = etexture_load(file_name_path);
        texture_id_resource += 1;
        printf("INFO: Resource load texture [%s]\n", filename);
    }

    if (id_temporal != -1)
    {
        g_hash_table_insert(hash_table, key, id_temporal);
    }
}

etexture ermine_resource_get_texture(const char *key)
{
    int id = g_hash_table_lookup(hash_table, key);
    return texture_resource_data[id];
}

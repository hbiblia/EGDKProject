
#include "ermine.h"
#include <glib.h>

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

// -------------
// RESOURCE::BASE
// -------------
void eresource_close(void)
{
    g_hash_table_destroy(hash_table);
}

void eresource_init(const char *path_project)
{
    hash_table = g_hash_table_new(g_str_hash, g_str_equal);

    // path resource del proyecto.
    path_resource[RESOURCE_PATH_PROJECT] = PATH_BUILD(path_project);
    path_resource[RESOURCE_PATH] = PATH_BUILD(path_project, "resource");
    path_resource[RESOURCE_PATH_ENGINE] = PATH_BUILD(g_get_current_dir(), "resource");

    printf("INFO: Resource path: [%s]\n", path_resource[RESOURCE_PATH]);
    printf("INFO: Resource path engine [%s]\n",path_resource[RESOURCE_PATH_ENGINE]);

    // Cargamos resource del engine
    eresource_assets_load(PATH_BUILD(path_resource[RESOURCE_PATH_ENGINE], "texture","icon_folder.png"), "resource::icon_folder");
    eresource_assets_load(PATH_BUILD(path_resource[RESOURCE_PATH_ENGINE], "texture","icon_level.png"), "resource::icon_level");
}

// -------------
// RESOURCE::PATHs
// -------------
const char *eresource_get_path(int path_id)
{
    return path_resource[path_id];
}

// -------------
// RESOURCE::LOADs
// -------------
void eresource_assets_load(const char *filename, const char *key)
{
    int id_temporal = -1;

    if (eutil_isfile_extension(filename, ".png") || eutil_isfile_extension(filename, ".jpg"))
    {
        id_temporal = texture_id_resource;
        texture_resource_data[texture_id_resource] = etexture_load(filename);
        texture_id_resource += 1;
        printf("INFO: Resource load texture [%s]\n", filename);
    }

    if (id_temporal != -1)
    {
        g_hash_table_insert(hash_table, key, id_temporal);
    }
}

// -------------
// RESOURCE::TEXTURE
// -------------

/*
 * Obtenemos la textura segun su key.
 *
 */

etexture eresource_get_texture(const char *key)
{
    int id = g_hash_table_lookup(hash_table, key);
    return texture_resource_data[id];
}

// -------------
// RESOURCE::LEVEL
// -------------

/*
 * Guardamos un level si no existe lo crea.
 *
 */

void eresource_level_save(const char *filename)
{
    const char *resource_path = eresource_get_path(RESOURCE_PATH);

    const char *json_world_data = flower_internal_serialize();

    FILE *file = fopen(PATH_BUILD(resource_path, filename), "w");
    if (file == NULL)
    {
        return 0;
    }

    fputs(json_world_data, file);
    fclose(file);
    printf("INFO: Save level [%s]\n", filename);
}

/*
 * Cargamos un level existente.
 *
 */
void eresource_level_open(const char *filename)
{
    const char *resource_path = eresource_get_path(RESOURCE_PATH);
    const char *file_level = PATH_BUILD(resource_path, filename);
}

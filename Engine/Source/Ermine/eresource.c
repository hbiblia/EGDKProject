
#include "ermine.h"
#include <glib.h>

#define MAX_RESOURCE_FILE 1000

/*
 * Resource: Administra los archivos
 * que se utilizan en el motor.
 */

static GHashTable *hash_table;

static int texture_id_resource = 0;
static etexture texture_resource_data[MAX_RESOURCE_FILE];

void eresource_close(void)
{
    g_hash_table_destroy(hash_table);
}

void eresource_init(void)
{
    hash_table = g_hash_table_new(g_str_hash, g_str_equal);
}

// cargamos los archivos soportados
void eresource_assets_load(const char *filename, const char *key)
{
    int id_temporal = -1;

    if(eutil_isfile_extension(filename,".png") || eutil_isfile_extension(filename,".jpg")){
        id_temporal = texture_id_resource;
        texture_resource_data[texture_id_resource] = etexture_load(filename);
        texture_id_resource += 1;
        printf("INFO: Resource load texture [%s]\n", filename);
    }

    if (id_temporal != -1){
        g_hash_table_insert(hash_table, key, id_temporal);
    }
}

// texture
etexture eresource_get_texture(const char *key)
{
    int id = g_hash_table_lookup(hash_table, key);
    return texture_resource_data[id];
}

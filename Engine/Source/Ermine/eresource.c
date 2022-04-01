
#include "ermine.h"
#include "flower.h"

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

// ---------------------------
// SCENE MANAGER SIMPLE
// ---------------------------
static bool scene_bopened = false;
static char *scene_name_file = NULL;
static char *scene_file = NULL;

// ---------------------------
// PROJECT assets.json
// ---------------------------
static JSON_Value *root_value;
static JSON_Array *commits;

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

    // assets.json
    root_value = json_parse_file(PATH_BUILD(path_resource[RESOURCE_PATH], "assets.json"));
    commits = json_value_get_array(root_value);

    // Cargamos los archivos soportados
    eresource_assets_game(commits);

    printf("INFO: Resource path: [%s]\n", path_resource[RESOURCE_PATH]);
    printf("INFO: Resource path engine [%s]\n", path_resource[RESOURCE_PATH_ENGINE]);
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

void eresource_assets_game(JSON_Array *commits)
{
    const char *resource_path = eresource_get_path(RESOURCE_PATH);

    // RESOURCE LOAD
    for (int i = 0; i < json_array_get_count(commits); i++)
    {
        JSON_Object *commit = json_array_get_object(commits, i);

        const char *name = json_object_get_string(commit, "name");
        const char *ext = json_object_get_string(commit, "ext");
        double uid = json_object_get_number(commit, "id");

        if (strlen(ext) == 0)
        {
            JSON_Array *children = json_object_get_array(commit, "children");
            eresource_assets_game(children);
            return;
        }

        gchar *fileName = PATH_BUILD(resource_path, STRDUPPF("r%.0f.%s", uid, ext));
        eresource_assets_load(fileName, name);
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
// RESOURCE::SCENE
// -------------

/*
 * Guardamos un level si no existe lo crea.
 *
 */

void eresource_scene_save(void)
{
    // if (scene_bopened)
    // {
    //     const char *resource_path = eresource_get_path(RESOURCE_PATH);
    //     const char *json_world_data = flower_internal_serialize();
    //     printf("O: %s\n", json_world_data);
    //     JSON_Value *value = json_parse_string(json_world_data);

    //     JSON_Status status = json_serialize_to_file(value, scene_file);
    // }

    printf("A: %s\n",flower_internal_serialize());
}

/*
 * Cargamos un level existente.
 *
 */
void eresource_scene_open(const char *name)
{
    JSON_Object *obj = eresource_assets_find_object("id", "3");
    JSON_Array *children = json_object_get_array(obj, "children");
    JSON_Object *result = eresource_assets_find_object_custom("name", name, children);

    int uid = (int)json_object_get_number(json_object(result), "id");

    scene_bopened = true;
    scene_name_file = STRDUPPF("r%d.scene", uid);

    const char *resource_path = eresource_get_path(RESOURCE_PATH);
    scene_file = PATH_BUILD(resource_path, scene_name_file);

    printf("INFO: Resource open scene: [%s]\n", name);
}

/*
 * Verificamos si tenemos una escena
 * abierta.
 *
 */
bool eresource_scene_is_open(void)
{
    return scene_bopened;
}

// ------------------------
// assets.json
// ------------------------

/*
 * Buscamos un Object
 *
 */

JSON_Object *eresource_assets_find_object_custom(const char *id_name, const char *value, JSON_Array *r)
{
    for (int i = 0; i < json_array_get_count(r); i++)
    {
        JSON_Object *commit = json_array_get_object(r, i);

        const char *type = json_object_get_string(commit, "type");

        if (json_object_has_value_of_type(commit, id_name, JSONNumber))
        {
            double val_out = json_object_get_number(commit, id_name);
            if (val_out == atof(value))
            {
                return commit;
            }
        }
        else if (json_object_has_value_of_type(commit, id_name, JSONString))
        {
            const char *val_out = json_object_get_string(commit, id_name);
            if (strcmp(val_out, value) == 0)
            {
                return commit;
            }
        }
        else
        {
            if (strcmp(type, "folder") == 0)
            {
                return eresource_assets_find_object_custom(id_name, value, json_object_get_array(commit, "children"));
            }
        }
    }
    return NULL;
}

JSON_Object *eresource_assets_find_object(const char *id_name, const char *value)
{
    return eresource_assets_find_object_custom(id_name, value, commits);
}

/*
 * Creamos un item nuevo
 *
 */

JSON_Value *eresource_assets_create_new_item(const char *name, const char *type, const char *ext)
{
    int uid = eutil_genrandom_number(4);

    JSON_Value *data = json_value_init_object();

    json_object_set_string(json_object(data), "name", name);
    json_object_set_string(json_object(data), "type", type);
    json_object_set_string(json_object(data), "ext", ext);
    json_object_set_number(json_object(data), "id", uid);

    if (strcmp(type, "folder") == 0)
    {
        json_object_set_value(json_object(data), "children", json_parse_string("[]"));
    }

    return data;
}

/*
 * Obtenemos el data principal del assets.json
 *
 */

JSON_Array *eresource_assets_get_main(void)
{
    return commits;
}

/*
 * Obtenemos el data principal del assets.json
 *
 */

JSON_Status eresource_assets_save(void)
{
    const char *resource_path = eresource_get_path(RESOURCE_PATH);
    JSON_Status status = json_serialize_to_file(root_value, PATH_BUILD(resource_path, "assets.json"));
    return status;
}

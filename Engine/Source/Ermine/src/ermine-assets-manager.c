#include "ermine-assets-manager.h"
#include "ermine-util.h"
#include "ermine-resource.h"

static JSON_Value *jroot_value = NULL;
static JSON_Array *jroots = NULL;
static char *jpath;

void ermine_assets_manager_init(const char *file_name)
{
    jroot_value = json_parse_file(file_name);
    jroots = json_value_get_array(jroot_value);

    // path default file
    jpath = STRDUP(file_name);

    // cargamos los assets al inicio
    ermine_assetsm_resource_load_content();
}

static JSON_Value *ermine_assetsm_get_rootv(void)
{
    return jroot_value;
}

JSON_Array *ermine_assetsm_get_roots(void)
{
    return jroots;
}

const char *ermine_assetsm_get_file_path(void)
{
    return jpath;
}

JSON_Object *ermine_assetsm_find_by_custom(const char *id, const char *value, JSON_Array *r)
{
    for (int i = 0; i < json_array_get_count(r); i++)
    {
        JSON_Object *commit = json_array_get_object(r, i);

        const char *type = json_object_get_string(commit, "type");

        if (json_object_has_value_of_type(commit, id, JSONNumber))
        {
            double val_out = json_object_get_number(commit, id);
            if (val_out == atof(value))
            {
                return commit;
            }
        }
        else if (json_object_has_value_of_type(commit, id, JSONString))
        {
            const char *val_out = json_object_get_string(commit, id);
            if (strcmp(val_out, value) == 0)
            {
                return commit;
            }
        }
        else
        {
            if (strcmp(type, "folder") == 0)
            {
                return ermine_assetsm_find_by_custom(id, value, json_object_get_array(commit, "children"));
            }
        }
    }
    return NULL;
}

JSON_Object *ermine_assetsm_find_by(const char *id, const char *value)
{
    return ermine_assetsm_find_by_custom(id, value, ermine_assetsm_get_roots());
}

JSON_Value *ermine_assetsm_new_object(const char *name, const char *type, const char *ext)
{
    int uid = ermine_random_number_len(4);

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

JSON_Status ermine_assetsm_save_file(void)
{
    JSON_Status status = json_serialize_to_file(ermine_assetsm_get_rootv(), ermine_assetsm_get_file_path());
    return status;
}

void ermine_assetsm_resource_load_content_custom(JSON_Array *roots)
{
    for (int i = 0; i < json_array_get_count(roots); i++)
    {
        JSON_Object *commit = json_array_get_object(roots, i);

        const char *name = json_object_get_string(commit, "name");
        const char *ext = json_object_get_string(commit, "ext");
        double uid = json_object_get_number(commit, "id");

        if (strlen(ext) == 0)
        {
            JSON_Array *children = json_object_get_array(commit, "children");
            ermine_assetsm_resource_load_content_custom(children);
            return;
        }

        char *file_name = STRDUPPF("r%.0f.%s", uid, ext);
        ermine_resource_load(file_name, name, RESOURCE_PATH);
    }
}

void ermine_assetsm_resource_load_content(void)
{
    ermine_assetsm_resource_load_content_custom(ermine_assetsm_get_roots());
}

#include "ermine-resource.h"
#include "ermine-string.h"
#include "ermine-path.h"
#include "ermine-file.h"

#include "ermine-ctexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "sokol/sokol_gfx.h"

static JSON_Value *resource_object[RESOURCE_OBJ_LAST];
static char *path_resource[RESOURCE_LAST];

// Se cargo bien el proyecto
static bool bproject = false;

void ermine_resource_init(const char *path_str)
{
    printf("RESOURCE: %s\n", path_str);

    // ENGINE
    path_resource[RESOURCE_PATH_ENGINE] = ermine_path_build(ermine_path_get_current(), "resource", NULL);
}

void ermine_resource_project(const char *project_path_str)
{
    // PROJECTS
    path_resource[RESOURCE_PATH_PROJECT] = ermine_strdup(project_path_str);
    path_resource[RESOURCE_PATH] = ermine_path_build(project_path_str, "resource", NULL);

    path_resource[RESOURCE_PROJECT] = ermine_path_build(path_resource[RESOURCE_PATH_PROJECT], "project.json", NULL);
    path_resource[RESOURCE_ASSETS] = ermine_path_build(path_resource[RESOURCE_PATH], "src", "assets.json", NULL);

    // Obtenemos el archivo de config del proyecto [assets, project]
    resource_object[RESOURCE_OPROJECT] = json_parse_file(path_resource[RESOURCE_PROJECT]);
    resource_object[RESOURCE_OASSETS] = json_parse_file(path_resource[RESOURCE_ASSETS]);
}

void ermine_resource_close(void)
{
    for (int i = 0; i < RESOURCE_OBJ_LAST; i++)
    {
        if (resource_object[i] != NULL)
            json_value_free(resource_object[i]);
    }
    for (int i = 0; i < RESOURCE_LAST; i++)
    {
        if (path_resource[i] != NULL)
            free(path_resource[i]);
    }

    printf("INFO: Resource free\n");
}

const char *ermine_resource_get_path(int id)
{
    return path_resource[id];
}

JSON_Value *ermine_resource_get_object(int id)
{
    return resource_object[id];
}


etexture ermine_resource_texture_file_load(const char *filename)
{
    etexture texture = {0};

    int comp;
    stbi_uc *data = stbi_load(filename, &texture.width, &texture.height, &comp, STBI_rgb_alpha);

    if (data != NULL)
    {
        sg_image d = sg_make_image(&(sg_image_desc){
            .width = texture.width,
            .height = texture.height,
            .data.subimage[0][0] = {
                .ptr = data,
                .size = (size_t){texture.width * texture.height * 4},
            },
        });
        texture.id = d.id;

        stbi_image_free(data);
    }

    return texture;
}

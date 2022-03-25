#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <eflecs.h>

#include <glib.h>
#include "parson/parson.h"

static JSON_Value *root_value;
static JSON_Array *commits;
static JSON_Object *commit;

void panel_assets_init(void)
{
    const char *path_resource = "D:\\Github\\EGDKProyect\\Examples\\TappyPlane\\resource\\";
    root_value = json_parse_file("D:\\Github\\EGDKProyect\\Examples\\TappyPlane\\resource\\assets.json");
    commits = json_value_get_array(root_value);

    // RESOURCE LOAD
    for (int i = 0; i < json_array_get_count(commits); i++)
    {
        commit = json_array_get_object(commits, i);

        const char *name = json_object_get_string(commit, "name");
        const char *ext = json_object_get_string(commit, "ext");
        double uid = json_object_get_number(commit, "id");

        gchar *fileName = g_strdup_printf("%sr%.0f.%s", path_resource, uid, ext);

        eresource_assets_load(fileName, name);
    }
}

void panel_assets_main(void)
{
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Assets", false, ImGuiWindowFlags_NoMove))
    {
        ImVec2 panelSize;
        igGetContentRegionAvail(&panelSize);

        static float padding = 16.0f;
        static float thumbnailSize = 64.0f;
        float cellSize = thumbnailSize + padding;

        float iconWidth = panelSize.x;
        int columnCount = (int)(iconWidth / cellSize);

        igColumns(columnCount, 0, false);
        {
            for (int i = 0; i < json_array_get_count(commits); i++)
            {
                commit = json_array_get_object(commits, i);
                const char *name = json_object_get_string(commit, "name");

                igPushID_Str(name);
                {
                    etexture image = eresource_get_texture(name);

                    igPushStyleColor_Vec4(ImGuiCol_Button, (ImVec4){0, 0, 0, 0});
                    igImageButton((ImTextureID)(uintptr_t)image.id, (ImVec2){thumbnailSize, thumbnailSize}, (ImVec2){0, 0}, (ImVec2){1, 1}, -1, (ImVec4){0, 0, 0, 0}, (ImVec4){1, 1, 1, 1});

                    // Draggable source
                    if (igBeginDragDropSource(0))
                    {
                        igSetDragDropPayload("ASSETS_ITEM", name, strlen(name)+1, 0);
                        igEndDragDropSource();
                    }
                    igPopStyleColor(1);

                    if (igIsItemHovered(0) && igIsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        printf("Selected: %s\n", name);
                    }

                    igTextWrapped("%s", name);
                    igNextColumn();
                }
                igPopID();
            }
        }
        igColumns(1, 0, false);
    }
    igEnd();
}

void assets_import()
{
}
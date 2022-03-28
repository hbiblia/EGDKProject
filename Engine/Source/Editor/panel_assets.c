#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <flower.h>

#include "parson/parson.h"

// ---------------------------
// ---------------------------
static double folder_selected_id = 0;

// ---------------------------
// JSON PARSE
// ---------------------------
static JSON_Value *root_value;
static JSON_Array *commits;
static JSON_Array *folder_selected = NULL;

void panel_assets_init(void)
{
    const char *resource_path = eresource_get_path(RESOURCE_PATH);
    root_value = json_parse_file(PATH_BUILD(resource_path, "assets.json"));
    commits = json_value_get_array(root_value);

    eresource_assets_game(commits);

    printf("INFO: Modulo assets resource completed\n");
}

void panel_assets_main(void)
{
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Assets", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
    {
        // ------------------------
        // Toolbar
        // ------------------------
        // if (igButton("Up folder", (ImVec2){0.0f, 0.0f}))
        // {
        // }
        // igSameLine(0.0f, 1.0f);
        if (igButton("Borrar", (ImVec2){0.0f, 0.0f}))
        {
        }
        igSameLine(0.0f, 3.0f);
        if (igButton("+", (ImVec2){25.0f, 0.0f}))
        {
            igOpenPopup_Str("assets-add-elements", 0);
        }
        if (igBeginPopup("assets-add-elements", 0))
        {
            if (igSelectable_Bool("Import file...", false, 0, (ImVec2){0, 0}))
            {
            }
            igSeparator();
            if (igSelectable_Bool("Folder", false, 0, (ImVec2){0, 0}))
            {
            }
            if (igSelectable_Bool("Component", false, 0, (ImVec2){0, 0}))
            {
            }
            if (igSelectable_Bool("System", false, 0, (ImVec2){0, 0}))
            {
            }
            if (igSelectable_Bool("Scene", false, 0, (ImVec2){0, 0}))
            {
            }
            igEndPopup();
        }
        igSeparator();

        // ------------------------
        // Content
        // ------------------------
        static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingMask_ | ImGuiTableFlags_NoSavedSettings;
        if (igBeginTable("assets_content", 2, flags, (ImVec2){0, 0}, 0.0f))
        {
            // ------------------------
            // Folder list
            // ------------------------
            // igTableSetColumnWidth(0, 300);
            igTableNextColumn();

            if (igBeginChild_Str("assets_folders_content", (ImVec2){0, 0}, 0, ImGuiWindowFlags_HorizontalScrollbar))
            {
                // ImGuiTreeNodeFlags_Leaf : Elimina el arrow
                for (int i = 0; i < json_array_get_count(commits); i++)
                {
                    JSON_Object *commit = json_array_get_object(commits, i);

                    const char *name = json_object_get_string(commit, "name");
                    const char *type = json_object_get_string(commit, "type");
                    double uid = json_object_get_number(commit, "id");

                    if (strcmp(type, "folder") == 0)
                    {
                        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding;

                        if (folder_selected_id == uid)
                        {
                            flags |= ImGuiTreeNodeFlags_Selected;
                        }
                        // if (strcmp(name, "/") == 0)
                        // {
                        //     flags |= ImGuiTreeNodeFlags_DefaultOpen;
                        // }
                        // si el folder es null, buscamos el resource
                        // para que sea el por defecto.
                        if(folder_selected == NULL && uid == 0){
                            folder_selected = json_object_get_array(commit, "children");
                        }

                        if (igTreeNodeEx_Str(name, flags))
                        {
                            igTreePop();
                        }
                        if (igIsItemClicked(ImGuiMouseButton_Left))
                        {
                            if (folder_selected_id != uid)
                            {
                                folder_selected = json_object_get_array(commit, "children");
                            }
                            folder_selected_id = uid;
                        }
                    }
                }
            }
            igEndChild();

            // ------------------------
            // List file folder open
            // ------------------------
            igTableNextColumn();

            ImVec2 panelSize;
            igGetContentRegionAvail(&panelSize);

            static float padding = 16.0f;
            static float thumbnailSize = 64.0f;
            float cellSize = thumbnailSize + padding;

            float iconWidth = panelSize.x;
            int columnCount = (int)(iconWidth / cellSize);
            if (columnCount < 1)
                columnCount = 1;

            if (igBeginTable("assets_content_items", columnCount, ImGuiTableFlags_ScrollY, (ImVec2){0, 0}, 0.0f))
            {
                for (int i = 0; i < json_array_get_count(folder_selected); i++)
                {
                    JSON_Object *commit = json_array_get_object(folder_selected, i);
                    const char *name = json_object_get_string(commit, "name");
                    const char *ext = json_object_get_string(commit, "ext");
                    const char *type = json_object_get_string(commit, "type");

                    igTableNextColumn();
                    igPushID_Str(name);
                    {
                        etexture icon = {0};

                        // ----------------------
                        // Iconos internos
                        // ----------------------
                        if (strcmp(type, "scene") == 0)
                        {
                            icon = eresource_get_texture("resource::iconScene");
                        }
                        else if (strcmp(type, "folder") == 0)
                        {
                            icon = eresource_get_texture("resource::iconFolder");
                        }else if (strcmp(type, "prefab") == 0)
                        {
                            icon = eresource_get_texture("resource::iconPrefab");
                        }else if (strcmp(type, "component") == 0)
                        {
                            icon = eresource_get_texture("resource::iconComponent");
                        }else if (strcmp(type, "system") == 0)
                        {
                            icon = eresource_get_texture("resource::iconSystem");
                        }
                        else
                        {
                            icon = eresource_get_texture(name);
                        }

                        igPushStyleColor_Vec4(ImGuiCol_Button, (ImVec4){0, 0, 0, 0});
                        igImageButton((ImTextureID)(uintptr_t)icon.id, (ImVec2){thumbnailSize, thumbnailSize}, (ImVec2){0, 0}, (ImVec2){1, 1}, -1, (ImVec4){0, 0, 0, 0}, (ImVec4){1, 1, 1, 1});

                        // ----------------------
                        // Draggable source
                        // ----------------------
                        if (igBeginDragDropSource(0))
                        {
                            igSetDragDropPayload("ASSETS_RESOURCE_ITEM", name, strlen(name) + 1, 0);
                            igEndDragDropSource();
                        }
                        igPopStyleColor(1);

                        // ----------------------
                        // DOUBLE CLICK ITEM
                        // ----------------------
                        if (igIsItemHovered(0) && igIsMouseDoubleClicked(ImGuiMouseButton_Left))
                        {
                            if (strcmp(type, "scene") == 0)
                            {
                                double uid = json_object_get_number(commit, "id");
                                editor_internal_scene_open(STRDUPPF("r%.0f", uid));
                            }
                        }

                        igTextWrapped("%s", name);
                    }
                    igPopID();
                }
                igEndTable();
            }
            igEndTable();
        }
    }
    igEnd();
}

void assets_import()
{
}

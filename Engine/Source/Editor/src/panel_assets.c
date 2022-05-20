#include <stdio.h>
#include <math.h>

#include "ermine-ecs.h"
#include "ermine-resource.h"
#include "ermine-string.h"
#include "ermine-path.h"
#include "ermine-ctexture.h"
#include "parson/parson.h"

#include "ermine-dialog.h"

#include "editor-internal.h"
#include "custom-imgui.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

// ---------------------------
// FILE o FOLDER SELECTED
// ---------------------------
static JSON_Object *item_selected = NULL;
static int item_selected_id_folder = -1;
static double folder_data_selected_id = 0;
static char *file_copy_name = NULL;
static bool bfile_copy = false;

// ---------------------------
// JSON PARSE
// ---------------------------
static JSON_Array *folder_data_selected = NULL;

// ---------------------------
// OTROS
// ---------------------------
static bool bcolumn0_width = false;
static double column0_default_size_width = 150.0;

// ---------------------------
// FUNCs
// ---------------------------

static void assets_ui_toolbar(void);

static void assets_ui_folder_list_column0();

static void assets_ui_list_folder_column1(void);

static void assets_ui_modal_create(const char *name, const char *title, const char *text_error, bool (*callback_fn)(const char *name));

static void assets_ui_folder_list_dir(JSON_Array *folders);

static bool assets_create_folder(const char *name);

static bool assets_create_component_file(const char *name);

bool assets_create_scene(const char *name);

static bool assets_is_virtual_item(JSON_Array *folder, const char *new_name, const char *type);

static void assets_delete_selected_item(void);

// ------------------------
// Assets-Init
// ------------------------

void panel_assets_init(void)
{
}

// ------------------------
// Assets-Renderer
// ------------------------

void panel_assets_main(void)
{
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Assets", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
    {
        // ------------------------
        // Toolbar
        // ------------------------
        assets_ui_toolbar();

        // ------------------------
        // Contenedor para la lista
        // de folder y lista de archivos.
        // ------------------------
        static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingMask_ | ImGuiTableFlags_NoSavedSettings | ImGuiTableColumnFlags_WidthFixed;
        igColumns(2, "assets_content", true);
        {
            // ------------------------
            // Lista de los folder
            // ------------------------

            assets_ui_folder_list_column0();
            igNextColumn();

            // BUG IMGUI:Columns Size Width
            if (!bcolumn0_width)
            {
                double width = ceil(igGetColumnWidth(0));
                bcolumn0_width = width >= column0_default_size_width - 1 ? true : false;
                igSetColumnWidth(0, (float)column0_default_size_width);
            }

            // ------------------------
            // Lista de los archivos de un folder
            // ------------------------
            assets_ui_list_folder_column1();
            igNextColumn();
        }
        igColumns(1, "assets_content", false);

        // ------------------------
        // Modals
        // ------------------------
        assets_ui_modal_create("Folder", "Create new folder", "Error occurred while creating a folder", assets_create_folder);
        assets_ui_modal_create("Rename", "Rename file", "Error occurred while creating a folder", assets_create_folder);
        assets_ui_modal_create("Component", "Create new component", "Error occurred while creating a component", assets_create_component_file);
        assets_ui_modal_create("Scene", "Create new scene", "Error occurred while creating a scene", assets_create_scene);
    }
    igEnd();
}

// ------------------------
// UI del toolbar
// ------------------------

void assets_import_file(const char *file)
{
    printf("ImportFile: %s\n", file);
}

void assets_ui_toolbar(void)
{
    // if (igButton("Borrar", (ImVec2){0.0f, 0.0f}))
    // {
    //     assets_delete_selected_item();
    // }

    // igSameLine(0.0f, 3.0f);

    if (igButton("+", (ImVec2){25.0f, 0.0f}))
    {
        imgui_OpenPopup("assets-add-elements");
    }

    if (imgui_BeginPopup("assets-add-elements"))
    {
        if (igSelectable_Bool("Import file...", false, 0, (ImVec2){0, 0}))
        {
            ermine_file_chooser_dialog_new("Import file...", "All\0*.*\0", assets_import_file);
        }

        igSeparator();

        if (igSelectable_Bool("Folder", false, 0, (ImVec2){0, 0}))
        {
            imgui_OpenPopup("Folder");
        }

        if (igSelectable_Bool("Component", false, 0, (ImVec2){0, 0}))
        {
            imgui_OpenPopup("Component");
        }

        if (igSelectable_Bool("System", false, 0, (ImVec2){0, 0}))
        {
        }

        if (igSelectable_Bool("Scene", false, 0, (ImVec2){0, 0}))
        {
            imgui_OpenPopup("Scene");
        }

        imgui_EndPopup();
    }

    igSeparator();
}

// ------------------------
// UI para la lista de folder
// ------------------------

void assets_ui_folder_list_column0()
{
    if (igBeginChild_Str("assets_folders_content", (ImVec2){0, 0}, 0, ImGuiWindowFlags_HorizontalScrollbar))
    {
        // ImGuiTreeNodeFlags_Leaf : Elimina el arrow
        // assets_ui_folder_list_dir(ermine_assetsm_get_roots());
    }
    igEndChild();
}

// ------------------------
// Listamos los folder
// ------------------------

void assets_ui_folder_list_dir(JSON_Array *folders)
{
    for (int i = 0; i < json_array_get_count(folders); i++)
    {
        JSON_Object *commit = json_array_get_object(folders, i);

        const char *name = json_object_get_string(commit, "name");
        const char *type = json_object_get_string(commit, "type");
        double uid = json_object_get_number(commit, "id");

        if (strcmp(type, "folder") == 0)
        {
            JSON_Array *temporal = json_object_get_array(commit, "children");

            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding;

            if (folder_data_selected_id == uid)
            {
                flags |= ImGuiTreeNodeFlags_Selected;
            }

            if (json_array_get_count(temporal) == 0)
            {
                flags |= ImGuiTreeNodeFlags_Leaf;
            }

            // si el folder es null, buscamos el resource
            // para que sea el por defecto.
            if (folder_data_selected == NULL && uid == 0)
            {
                folder_data_selected = temporal;
            }

            //
            bool bopened = igTreeNodeEx_Str(name, flags);
            if (igIsItemClicked(ImGuiMouseButton_Left))
            {
                if (folder_data_selected_id != uid)
                {
                    folder_data_selected = temporal;
                    item_selected = commit;
                    item_selected_id_folder = i;
                }
                folder_data_selected_id = uid;
            }
            if (bopened)
            {
                JSON_Array *childrens = temporal;
                assets_ui_folder_list_dir(childrens);
                igTreePop();
            }
        }
    }
}

// ------------------------
// UI para la lista de archivos
// de un folder que esta
// seleccionado.
// ------------------------

void assets_ui_list_folder_column1(void)
{
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
        for (int i = 0; i < json_array_get_count(folder_data_selected); i++)
        {
            JSON_Object *commit = json_array_get_object(folder_data_selected, i);
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
                // if (strcmp(type, "scene") == 0)
                // {
                //     icon = ermine_resource_get_texture("resource::iconScene");
                // }
                // else if (strcmp(type, "folder") == 0)
                // {
                //     icon = ermine_resource_get_texture("resource::iconFolder");
                // }
                // else if (strcmp(type, "prefab") == 0)
                // {
                //     icon = ermine_resource_get_texture("resource::iconPrefab");
                // }
                // else if (strcmp(type, "component") == 0)
                // {
                //     icon = ermine_resource_get_texture("resource::iconComponent");
                // }
                // else if (strcmp(type, "system") == 0)
                // {
                //     icon = ermine_resource_get_texture("resource::iconSystem");
                // }
                // else
                // {
                //     icon = ermine_resource_get_texture(name);
                // }

                // igPushStyleColor_Vec4(ImGuiCol_Button, (ImVec4){0, 0, 0, 0});
                // if (igImageButton((ImTextureID)(uintptr_t)icon.id, (ImVec2){thumbnailSize, thumbnailSize}, (ImVec2){0, 0}, (ImVec2){1, 1}, -1, (ImVec4){0, 0, 0, 0}, (ImVec4){1, 1, 1, 1}))
                // {
                //     item_selected = commit;
                //     item_selected_id_folder = i;
                //     printf("INFO: Selected item [%s]\n", name);
                // }

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
                // MENU CONTEXT ITEM
                // ----------------------
                if (igIsItemClicked(ImGuiMouseButton_Right))
                {
                    igOpenPopup_Str("context-menu-file", 0);
                }
                if (igBeginPopupContextItem("context-menu-file", ImGuiPopupFlags_MouseButtonRight))
                {
                    igText("File %s", name);
                    igSeparator();
                    if (igSelectable_Bool("Delete", false, 0, (ImVec2){0, 0}))
                    {
                        assets_delete_selected_item();
                    }
                    if (igSelectable_Bool("Rename", false, 0, (ImVec2){0, 0}))
                    {
                        imgui_OpenPopup("Rename");
                    }
                    igSeparator();
                    if (igSelectable_Bool("Copiar", false, 0, (ImVec2){0, 0}))
                    {
                        file_copy_name = ermine_strdup(name);
                    }
                    if (igSelectable_Bool("Duplicar", false, 0, (ImVec2){0, 0}))
                    {
                    }
                    if (igSelectable_Bool("Mover", false, 0, (ImVec2){0, 0}))
                    {
                    }
                    if (strcmp(type, "folder") == 0 && file_copy_name != NULL)
                    {
                        igSeparator();
                        if (igSelectable_Bool(ermine_strdup_printf("Pegar... %s", file_copy_name), false, 0, (ImVec2){0, 0}))
                        {
                        }
                    }
                    igEndPopup();
                }

                // ----------------------
                // DOUBLE CLICK ITEM
                // ----------------------
                if (igIsItemHovered(0) && igIsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    if (strcmp(type, "scene") == 0)
                    {
                        editor_internal_open_scene(name);
                    }
                }
                igTextWrapped("%s", name);
            }
            igPopID();
        }
        igEndTable();
    }
}

// ------------------------
// UI MODAL para crear archivos.
// ------------------------

void assets_ui_modal_create(const char *name, const char *title, const char *text_error, bool (*callback_fn)(const char *name))
{
    ImGuiViewport *viewport = igGetMainViewport();
    ImVec2 center;

    ImGuiViewport_GetCenter(&center, viewport);
    igSetNextWindowPos(center, ImGuiCond_Appearing, (ImVec2){0.5f, 0.5f});
    igSetNextWindowSize((ImVec2){300.0f, 0.0f}, ImGuiCond_None);

    if (igBeginPopupModal(name, NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
    {
        static char *buffer;
        static int state = 0;

        igText(title);

        // igSetKeyboardFocusHere(0);
        igInputText("Name", buffer, sizeof(buffer), 0, NULL, NULL);

        if (state == -1)
        {
            igTextColored((ImVec4){1.0f, 0.0f, 0.0f, 1.0f}, text_error);
        }

        igSeparator();

        if (igButton("Create", (ImVec2){0, 0}))
        {
            if (callback_fn)
            {
                if (callback_fn(buffer) && strlen(buffer) > 0)
                {
                    buffer = ermine_strdup_printf("");
                    igCloseCurrentPopup();
                    state = 0;
                }
                else
                {
                    state = -1;
                }
            }
        }

        igSameLine(0.0f, 10.0f);

        if (igButton("Cancel", (ImVec2){0, 0}))
        {
            state = 0;
            igCloseCurrentPopup();
        }

        igEndPopup();
    }
}

// ------------------------
// Comprobamos si existe otro
// item con el mismo nombre
// ------------------------

bool assets_is_virtual_item(JSON_Array *folder, const char *new_name, const char *type)
{
    for (int i = 0; i < json_array_get_count(folder); i++)
    {
        JSON_Object *commit = json_array_get_object(folder, i);
        const char *name = json_object_get_string(commit, "name");
        const char *type = json_object_get_string(commit, "type");
        if (strcmp(name, new_name) == 0 && strcmp(type, type) == 0)
        {
            return true;
        }
    }
    return false;
}

// ------------------------
// Borramos un folder seleccionado
// ------------------------

void assets_delete_selected_item(void)
{
    if (item_selected_id_folder != -1)
    {
        const char *type = json_object_get_string(item_selected, "type");
        const char *name = json_object_get_string(item_selected, "name");

        json_array_remove(folder_data_selected, item_selected_id_folder);
        if (!strcmp(type, "folder") == 0)
        {
            // Otras cosas que se deben hacer si no es un folder.
        }

        item_selected_id_folder = -1;

        printf("INFO: Delete item [%s]\n", name);

        // Actualizamos el assets.json
        // JSON_Status status = ermine_assetsm_save_file();
    }
}

bool assets_create_folder(const char *name)
{
    printf("INFO: Create folder [%s]", name);

    // if (assets_is_virtual_item(folder_data_selected, name, "folder"))
    // {
    //     goto error;
    // }

    // JSON_Value *data = ermine_assetsm_new_object(name, "folder", "");
    // json_array_append_value(folder_data_selected, data);

    // // Actualizamos el assets.json
    // JSON_Status status = ermine_assetsm_save_file();
    // if (!status)
    // {
    //     printf("[OK]\n");
    //     return true;
    // }
    // else
    // {
    // error:

    //     printf("[No]\n");
    //     return false;
    // }
}

bool assets_create_component_file(const char *name)
{
//     printf("INFO: Create component [%s]", name);

//     JSON_Object *folder = ermine_assetsm_find_by("id", "1");
//     if (!json_object_has_value(folder, "children"))
//         goto error;
//     JSON_Array *children = json_object_get_array(folder, "children");

//     if (assets_is_virtual_item(children, name, "component"))
//         goto error;

//     size_t count_old = json_array_get_count(children);

//     // Creamos el item para assets.json
//     JSON_Value *new_item = ermine_assetsm_new_object(name, "component", "json");
//     JSON_Status status = json_array_append_value(children, new_item);
//     int uid = (int)json_object_get_number(json_object(new_item), "id");

//     if (status == JSONFailure)
//         goto error;

//     // Creamos el objecto para el json-file
//     const char *resource_path = ermine_resource_get_path(RESOURCE_PATH);
//     JSON_Value *data = json_value_init_object();
//     json_object_set_string(json_object(data), "name", name);
//     json_object_set_value(json_object(data), "property", json_parse_string("[]"));
//     json_serialize_to_file(data, ermine_path_build(resource_path, ermine_strdup_printf("c%d.json", uid), NULL));

//     // Actualizamos el assets.json
//     status = ermine_assetsm_save_file();
//     if (status == JSONSuccess)
//     {
//         printf("[OK]\n");
//         return true;
//     }

// error:
//     printf("[No]\n");
//     return false;
}

bool assets_create_scene(const char *name)
{
    printf("INFO: Create scene [%s]", name);

//     JSON_Object *folder = ermine_assetsm_find_by("id", "3");
//     if (!json_object_has_value(folder, "children"))
//         goto error;
//     JSON_Array *children = json_object_get_array(folder, "children");

//     if (assets_is_virtual_item(children, name, "scene"))
//         goto error;

//     size_t count_old = json_array_get_count(children);

//     // Creamos el item para assets.json
//     JSON_Value *new_item = ermine_assetsm_new_object(name, "scene", "scene");
//     JSON_Status status = json_array_append_value(children, new_item);
//     int uid = (int)json_object_get_number(json_object(new_item), "id");

//     if (status == JSONFailure)
//         goto error;
    
//     const char *resource_path = ermine_resource_get_path(RESOURCE_PATH);
//     json_serialize_to_file(json_parse_string("{}"), ermine_path_build(resource_path, ermine_strdup_printf("r%d.scene", uid), NULL));

//     // Actualizamos el assets.json
//     status = ermine_assetsm_save_file();
//     if (status == JSONSuccess)
//     {
//         printf("[OK]\n");
//         return true;
//     }

// error:
//     printf("[No]\n");
//     return false;
}
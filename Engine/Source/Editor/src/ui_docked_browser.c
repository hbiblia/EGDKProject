#include "ui_docked_browser.h"
#include "editor_data.h"
#include "custom-imgui.h"
#include "ermine-string.h"
#include "ermine-ui.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

const char *filtro_file_import = "All\0*.*\0Texture (*.png)\0*.png\0Texture (*.jpg)\0*.jpg\0Texture (*.jpeg)\0*.jpeg\0JSON file (*.json)\0*.json\0TrueType Font (*.ttf)\0*.ttf\0Wave Audio File (*.wav)\0*.wav\0";

static void docked_browser_import_file(void)
{
    ermine_file_chooser_dialog_new("Import file...",filtro_file_import, NULL);
}

static void ui_docked_browser_menubar(void)
{
    if (imgui_BeginPopup("assets-add-elements"))
    {
        if (igSelectable_Bool("Import file...", false, 0, (ImVec2){0, 0}))
        {
            docked_browser_import_file();
        }

        igSeparator();

        if (igSelectable_Bool("New Folder", false, 0, (ImVec2){0, 0}))
        {
            ermine_ui_dialog_input_new(&(ermine_ui_dialog_desc_t){
                .title = "Folder",
                .desc="Create new folder",
                .text_error = "Error occurred while creating a folder"
            });
        }

        igSeparator();

        if (igSelectable_Bool("Component", false, 0, (ImVec2){0, 0}))
        {
        }

        if (igSelectable_Bool("System", false, 0, (ImVec2){0, 0}))
        {
        }

        if (igSelectable_Bool("Level", false, 0, (ImVec2){0, 0}))
        {
        }

        imgui_EndPopup();
    }
}

static void ui_docked_browser_toolbar(void)
{
    ui_docked_browser_menubar();

    if (igButton("+ Add", (ImVec2){0, 0.0f}))
    {
        imgui_OpenPopup("assets-add-elements");
    }

    igSameLine(0.0f, 5.0f);

    if (igButton("/ Import", (ImVec2){0, 0.0f}))
    {
        docked_browser_import_file();
    }

    // igSameLine(0.0f, 5.0f);

    // if (igButton("Save all", (ImVec2){0, 0.0f}))
    // {
    // }

    igSeparator();
}

void ui_docked_browser_init(void)
{
}

void ui_docked_browser_render(void)
{
    
    igSetNextWindowSize((ImVec2){200, 200}, 0);
    if (igBegin("Content Browser", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar))
    {
        ermine_ui_process();
        ui_docked_browser_toolbar();
    }
    igEnd();
}
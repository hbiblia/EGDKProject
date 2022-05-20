#include "ui_docked_browser.h"
#include "editor_data.h"
#include "custom-imgui.h"
#include "ermine-string.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

static void ui_docked_browser_modal_create_file(const char *name, const char *title, 
    const char *text_error, bool (*fn)(const char *name))
{
    ImGuiViewport *viewport = igGetMainViewport();
    ImVec2 center;

    ImGuiViewport_GetCenter(&center, viewport);
    igSetNextWindowPos(center, ImGuiCond_Appearing, (ImVec2){0.5f, 0.5f});
    igSetNextWindowSize((ImVec2){300.0f, 0.0f}, ImGuiCond_None);

    if (igBeginPopupModal(name, NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
    {
        char *buffer = ermine_strdup("new folder");
        static int state = 0;

        igText(title);

        // igSetKeyboardFocusHere(0);
        igInputText("Name", buffer, 256, 0, NULL, NULL);

        if (state == -1)
        {
            igTextColored((ImVec4){1.0f, 0.0f, 0.0f, 1.0f}, text_error);
        }

        igSeparator();

        if (igButton("Create", (ImVec2){0, 0}))
        {
            printf("LOG: %s\n",buffer);
            if (fn)
            {
                if (fn(buffer) && strlen(buffer) > 0)
                {
                    buffer = "\0";
                    igCloseCurrentPopup();
                    state = 0;
                }
                else
                {
                    state = -1;
                }
            }
            else
            {
                state = 0;
                igCloseCurrentPopup();
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

static void docked_browser_import_file(void)
{
    ermine_file_chooser_dialog_new("Import file...",
                                   "Texture (*.png)\0*.png\0Texture (*.jpg)\0*.jpg\0Texture (*.jpeg)\0*.jpeg\0JSON file (*.json)\0*.json\0TrueType Font (*.ttf)\0*.ttf\0Wave Audio File (*.wav)\0*.wav\0", NULL);
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
            imgui_OpenPopup("Folder");
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
        ui_docked_browser_toolbar();

        // modals
        ui_docked_browser_modal_create_file("Folder", "Create new folder", "Error occurred while creating a folder", NULL);
    }
    igEnd();
}
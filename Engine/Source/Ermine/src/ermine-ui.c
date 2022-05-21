#include "ermine-ui.h"
#include "ermine-window.h"
#include "ermine-string.h"

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
// #include "sokol/sokol_glue.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

#define SOKOL_IMGUI_IMPL
#include "sokol/sokol_imgui.h"

static ermine_ui_dialog_desc_t dialog = {
    .title = "none"};

void ermine_ui_init(int samples)
{
    printf("INFO: Init CImGui\n");

    simgui_setup(&(simgui_desc_t){
        .sample_count = sapp_sample_count()});

    ImGuiIO *io = igGetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigDockingWithShift = true;
}

void ermine_ui_frame(void)
{
    simgui_new_frame(&(simgui_frame_desc_t){
        .width = ermine_window_width(),
        .height = ermine_window_height(),
        .delta_time = ermine_window_delta(),
        .dpi_scale = ermine_window_dpi(),
    });
}

void ermine_ui_draw(void)
{
    simgui_render();
}

void ermine_ui_event(const void *ev)
{
    const sapp_event *event = (sapp_event *)ev;
    simgui_handle_event(event);
}

void ermine_ui_close(void)
{
    simgui_shutdown();
}

// ----------------------------
// WINDOW SYSTEM
// ----------------------------

// ----------------------------
// DIALOG SYSTEM
// ----------------------------
static void ermine_ui_dialog_process(void)
{
    ImGuiViewport *viewport = igGetMainViewport();
    ImVec2 center;

    ImGuiViewport_GetCenter(&center, viewport);
    igSetNextWindowPos(center, ImGuiCond_Appearing, (ImVec2){0.5f, 0.5f});
    igSetNextWindowSize((ImVec2){dialog.size.x, dialog.size.y}, ImGuiCond_None);

    if (igBeginPopupModal(dialog.title, &dialog.is_show, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
    {
        static int state = 0;

        // descripción
        if (dialog.desc != NULL)
        {
            igText(dialog.desc);
        }

        // --------------------
        // donde se renderizara el contenido
        // --------------------
        igInputText("Name", dialog.inputvalue, 256, 0, NULL, NULL);

        // --------------------
        // text error
        // --------------------
        if (state == -1 && dialog.text_error != NULL)
        {
            igTextColored((ImVec4){1.0f, 0.0f, 0.0f, 1.0f}, dialog.text_error);
        }

        igSeparator();

        // --------------------
        // Botones
        // --------------------
        if (igButton(dialog.btn1_label, (ImVec2){0, 0}))
        {
            if (dialog.callback)
            {
                if (dialog.callback(dialog.inputvalue) && strlen(dialog.inputvalue) > 0)
                {
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

        if (igButton(dialog.btn2_label, (ImVec2){0, 0}))
        {
            state = 0;
            igCloseCurrentPopup();
            ermine_ui_dialog_close();
        }
        igEndPopup();
    }

    if (dialog.bfirst)
    {
        igOpenPopup_Str(dialog.title, 0);
        dialog.bfirst = false;
    }
}

//
void ermine_ui_process(void)
{
    ermine_ui_dialog_process();
}

void ermine_ui_dialog_input_new(const ermine_ui_dialog_desc_t *dialog_desc)
{
    dialog = *dialog_desc;

    // dialog.desc = dialog_desc->desc == NULL ? "" : dialog_desc->desc;
    dialog.btn1_label = dialog_desc->btn1_label == NULL ? "Ok" : dialog_desc->btn1_label;
    dialog.btn2_label = dialog_desc->btn2_label == NULL ? "Cancel" : dialog_desc->btn2_label;
    // dialog.text_error = dialog_desc->text_error == NULL ? "" : dialog_desc->text_error;
    // dialog.placeholder = dialog_desc->placeholder == NULL ? "" : dialog_desc->placeholder;

    dialog.inputvalue = ermine_strdup("");
    dialog.is_show = true;
    dialog.bfirst = true;
}

void ermine_ui_dialog_close(void)
{
    dialog.is_show = false;
}

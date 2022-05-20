#include "ui_editor_main.h"
#include "ui_editor_menubar.h"
#include "ui_docked_hierarchy.h"
#include "ui_docked_inspector.h"
#include "ui_docked_browser.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

// config de la docked-window
static ImGuiWindowFlags window_flags;
static ImGuiDockNodeFlags dockspace_flags;

// si ya tenemos completado el docked-build.
static bool bMainDockedCompletedOnce = false;

// funcs
static void dockspace_build(ImGuiViewport *viewport);
static ImGuiViewport *dockspace_begin(void);
static void dockspace_end(void);

void editor_main_init(void)
{
    // FLAGS WINDOWS UI
    // -------------
    window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;

    bMainDockedCompletedOnce = false;

    ui_docked_hierarchy_init();
    ui_docked_inspector_init();
    ui_docked_browser_init();
}

void editor_main_render(void)
{
    ImGuiViewport *viewport = dockspace_begin();
    {
        // DOCKSPACE BUILD
        // --------------
        dockspace_build(viewport);

        // MENUBAR
        // --------------
        ui_editor_menubar();
    }
    dockspace_end();

    // DOCKEDs
    // --------------
    // Dockeds ya estan registrados solo los cargamos.

    panel_viewport_main();
    ui_docked_hierarchy_render();
    ui_docked_inspector_render();
    ui_docked_browser_render();
}

ImGuiViewport *dockspace_begin(void)
{
    ImGuiViewport *viewport = igGetMainViewport();
    igSetNextWindowPos(viewport->Pos, 0, (ImVec2){0});
    igSetNextWindowSize(viewport->Size, 0);
    igSetNextWindowViewport(viewport->ID);
    igPushStyleVar_Float(ImGuiStyleVar_WindowRounding, 0.0f);

    igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f, 0.0f});
    igBegin("DockSpace", NULL, window_flags);
    igPopStyleVar(1);

    return viewport;
}

void dockspace_end(void)
{
    igPopStyleVar(1);
    igEnd();
}

void dockspace_build(ImGuiViewport *viewport)
{
    ImGuiStyle *style = igGetStyle();
    float minWinSizeX = style->WindowMinSize.x;
    style->WindowMinSize.x = 200.0f;

    ImGuiID dockspace_id = igGetID_Str("MyDockSpace");
    igDockSpace(dockspace_id, (ImVec2){0.0f, 0.0f}, dockspace_flags, (ImGuiWindowClass *)0);
    style->WindowMinSize.x = minWinSizeX;

    // #BUILDER
    if (!bMainDockedCompletedOnce)
    {
        bMainDockedCompletedOnce = true;
        igDockBuilderRemoveNode(dockspace_id);
        {
            igDockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
            igDockBuilderSetNodeSize(dockspace_id, viewport->Size);

            ImGuiID panel_left = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.155f, NULL, &dockspace_id);
            // ImGuiID panel_top = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.80f, NULL, &dockspace_id);
            ImGuiID panel_right = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.25f, NULL, &dockspace_id);
            ImGuiID panel_bottom = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.30f, NULL, &dockspace_id);

            // ID docks
            igDockBuilderDockWindow("Hierarchy", panel_left);
            igDockBuilderDockWindow("Viewport", dockspace_id);
            igDockBuilderDockWindow("Inspector", panel_right);
            igDockBuilderDockWindow("Content Browser", panel_bottom);
        }
    }
    igDockBuilderFinish(dockspace_id);
}
#include <stdio.h>

#define CIMGUI_IMPL
#include <ermine.h>
#include <ermine-flower.h>
#include "ermine-scene.h"
#include "ermine-string.h"

#include "editor-internal.h"

void editor_main_render();

void init()
{
    // CONFIG IMGUI
    // -------------

    ImGuiIO *io = igGetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigDockingWithShift = true;

    editor_internal_resource_default();
    ermine_scene_init();

    // PANELS INIT
    // -------------
    panel_viewport_init();
    panel_hierarchy_init();
    panel_inspector_init();
    panel_assets_init();
    
}

void update()
{
    // PANELS RENDER
    // -------------
    editor_main_render();
}

void before_update()
{
}

int main(int argc, char *argv[])
{
    printf("EGDKEditor v1.0-dev \n");

    ewindow_init((ewindow_desc){
        .title = STRDUPPF("EGDKEditor - %s", BASENAME(argv[1])),
        .width = 1280,
        .height = 700,
        .init_fn = init,
        .update_fn = update,
        .before_update = before_update,
        .path_project = argv[1],
    });
}

void editor_main_render()
{
    // FLAGS
    // -------------
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;

    // CONFIG STYLE
    // --------------

    ImGuiViewport *viewport = igGetMainViewport();
    igSetNextWindowPos(viewport->Pos, 0, (ImVec2){0});
    igSetNextWindowSize(viewport->Size, 0);
    igSetNextWindowViewport(viewport->ID);
    igPushStyleVar_Float(ImGuiStyleVar_WindowRounding, 0.0f);

    igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f, 0.0f});
    igBegin("DockSpace", NULL, window_flags);
    igPopStyleVar(1);
    {
        // DOCKSPACE
        // --------------

        ImGuiStyle *style = igGetStyle();
        float minWinSizeX = style->WindowMinSize.x;
        style->WindowMinSize.x = 200.0f;

        ImGuiID dockspace_id = igGetID_Str("MyDockSpace");
        igDockSpace(dockspace_id, (ImVec2){0.0f, 0.0f}, dockspace_flags, (ImGuiWindowClass *)0);
        style->WindowMinSize.x = minWinSizeX;

        // #BUILDER
        static bool first_time = true;
        if (first_time)
        {
            first_time = false;
            igDockBuilderRemoveNode(dockspace_id);
            {
                igDockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
                igDockBuilderSetNodeSize(dockspace_id, viewport->Size);

                ImGuiID panel_left = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.155f, NULL, &dockspace_id);
                // ImGuiID panel_top = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.80f, NULL, &dockspace_id);
                ImGuiID panel_right = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.25f, NULL, &dockspace_id);
                ImGuiID panel_bottom = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.30f, NULL, &dockspace_id);

                igDockBuilderDockWindow("Hierarchy", panel_left);
                igDockBuilderDockWindow("Viewport", dockspace_id);
                igDockBuilderDockWindow("Inspector", panel_right);
                igDockBuilderDockWindow("Assets", panel_bottom);
            }
        }
        igDockBuilderFinish(dockspace_id);

        // MENUBAR
        // --------------

        if (igBeginMenuBar())
        {
            if (igBeginMenu("File", true))
            {
                if (igMenuItem_Bool("New", "Ctrl+N", false, true))
                {
                }
                if (igMenuItem_Bool("Open", "Ctrl+O", false, true))
                {
                }
                if (igMenuItem_Bool("Save As...", "Ctrl+S", false, true))
                {
                    ermine_scene_save();
                }
                if (igMenuItem_Bool("Exit", "", false, true))
                {
                    ewindow_close();
                }
                igEndMenu();
            }
            igEndMenuBar();

        }
    }
    igPopStyleVar(1);
    igEnd();

    // PANELS
    // --------------

    panel_viewport_main();
    panel_inspector_main();
    panel_hierarchy_main();
    panel_assets_main();

}

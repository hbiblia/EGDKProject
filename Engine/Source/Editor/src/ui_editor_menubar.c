#include "ui_editor_menubar.h"

#include "ermine-window.h"

void ui_editor_menubar(void)
{
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
            }
            if (igMenuItem_Bool("Exit", "", false, true))
            {
                ermine_window_close();
            }
            igEndMenu();
        }
        igEndMenuBar();
    }
}

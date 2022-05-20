#include "ermine-dialog.h"
#include <windows.h>

void ermine_file_chooser_dialog_new(const char *title, const char *filter, void (*callback)(const char *file))
{
#if defined(WINDOWS)
    OPENFILENAME ofn;        // common dialog box structure
    TCHAR szFile[260] = {0}; // if using TCHAR macros

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    // ofn.hwndOwner = hWnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = title;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        if (callback)
        {
            callback(ofn.lpstrFile);
        }
    }
#endif

#if defined(LINUX)
    printf("Linux\n");
#endif

#if defined(DARWIN)
    printf("MAC - DARWIN\n");
#endif
}
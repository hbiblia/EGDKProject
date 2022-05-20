#ifndef ERMINE_CIMGUI_H
#define ERMINE_CIMGUI_H
#include <stdio.h>
#include <stdlib.h>
#include "ermine.h"

ermine_private void ermine_ui_init(int samples);
ermine_private void ermine_ui_frame(void);
ermine_private void ermine_ui_draw(void);
ermine_private void ermine_ui_close(void);
ermine_private void ermine_ui_event(const void *ev);

#endif //ERMINE_CIMGUI_H
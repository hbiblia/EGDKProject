#ifndef ERMINE_CIMGUI_H
#define ERMINE_CIMGUI_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ermine.h"
#include "ermine-cmath.h"

typedef struct ermine_ui_dialog_desc_t
{
    char *title;
    char *desc;
    char *text_error;
    char *placeholder;
    char *btn1_label;
    char *btn2_label;
    char *inputvalue;
    int type;
    evec2 size;
    bool is_show;
    bool bfirst;
    bool (*callback)(const char *name);
}ermine_ui_dialog_desc_t;

ermine_private void ermine_ui_init(int samples);
ermine_private void ermine_ui_frame(void);
ermine_private void ermine_ui_draw(void);
ermine_private void ermine_ui_close(void);
ermine_private void ermine_ui_event(const void *ev);

ermine_public void ermine_ui_process(void);
ermine_public void ermine_ui_dialog_input_new(const ermine_ui_dialog_desc_t *dialog_desc);

#endif //ERMINE_CIMGUI_H
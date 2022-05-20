#ifndef ERMINE_DIALOG_H
#define ERMINE_DIALOG_H
#include <stdio.h>
#include "ermine.h"

ermine_public void ermine_file_chooser_dialog_new(const char *title, const char *filter, void (*callback)(const char *file));

#endif // ERMINE_DIALOG_H
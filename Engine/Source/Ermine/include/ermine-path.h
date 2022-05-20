#ifndef ERMINE_PATH_H
#define ERMINE_PATH_H
#include <stdio.h>
#include "ermine.h"

#if defined(_WIN32)
    #define SEPARATOR_OS '\\'
#else
    #define SEPARATOR_OS '/'
#endif

ermine_public char *ermine_path_normalize(const char *path);
ermine_public const char *ermine_path_get_current(void);
ermine_public const char *ermine_path_build(const char *format, ...);

#endif // ERMINE_PATH_H
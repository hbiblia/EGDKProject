#ifndef ERMINE_STRING_H
#define ERMINE_STRING_H
#include <glib.h>
#include "ermine.h"

#define STRDUPPF    g_strdup_printf
#define STRDUP      g_strdup
#define PATH_BUILD(...) eutil_path_normalize(g_build_filename(__VA_ARGS__, NULL))

#endif // ERMINE_STRING_H

#include "ermine-string.h"
#include <glib.h>
#include <stdbool.h>
#include <stdint.h>

int32_t ermine_strlen(const char *str)
{
    return g_utf8_strlen(str, 0);
}

char *ermine_strreverse(const char *str)
{
    return g_utf8_strreverse(str, ermine_strlen(str));
}

char *ermine_substring(const char *str, int start, int end)
{
    return g_utf8_substring(str, (glong)start, (glong)end);
}

char *ermine_strcat(char *dest, const char *src)
{
    return strcat(dest, src);
}

char *ermine_strncpy(char *dest, const char *src, size_t n)
{
    return g_utf8_strncpy(dest, src, n);
}

char *ermine_strdup(const char *str)
{
    return g_strdup(str);
}

char *ermine_strdup_printf(const char *format, ...)
{
    char buffer[256] = {0};

    va_list args;
    va_start(args, format);
    {
        vsprintf(buffer, format, args);
    }
    va_end(args);

    return ermine_strdup(buffer);
}

char *ermine_strreplace(const char *str, const char *find, const char *replace)
{
    GString *gstr = g_string_new(str);
    g_string_replace(gstr, find, replace, 0);
    return g_string_free(gstr, false);
}
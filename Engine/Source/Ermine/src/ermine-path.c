#include "ermine-path.h"
#include "ermine-string.h"
#include <stdarg.h>

char *ermine_path_normalize(const char *path)
{
    char *new_path = NULL;
#if defined(_WIN32)
    new_path = ermine_strreplace(path, "/", "\\");
#else
    new_path = ermine_strreplace(path, "\\", "/");
#endif
    return new_path;
}

const char *ermine_path_get_current(void)
{
    char buffer[FILENAME_MAX];

#if defined(_WIN32)
    _getcwd(buffer, FILENAME_MAX);
#else
    getcwd(buffer, FILENAME_MAX);
#endif

    return ermine_strdup(buffer);
}

const char *ermine_path_build(const char *format, ...)
{
    char buffer[256] = {0};
    va_list args;
    va_start(args, format);
    {
        ermine_strcat(buffer, format);

        while (1)
        {
            const char *path = va_arg(args, char *);
            if (path == NULL)
                break;

            ermine_strcat(buffer, SEPARATOR_OS == '/' ? "/" : "\\");
            ermine_strcat(buffer, path);
        }
    }
    va_end(args);
    return ermine_path_normalize(ermine_strdup(buffer));
}
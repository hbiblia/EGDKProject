#include "ermine.h"
#include <stdarg.h>

/*
 * Utility
 *
 */

unsigned char *eutil_loadfile_data(const char *filename, unsigned int *bytes)
{
    unsigned char *data = NULL;
    *bytes = 0;

    if (filename != NULL)
    {
        FILE *file = fopen(filename, "rb");
        if (file != NULL)
        {
            fseek(file, 0, SEEK_END);
            int size = ftell(file);
            fseek(file, 0, SEEK_SET);

            if (size > 0)
            {
                data = (unsigned char *)malloc(size * sizeof(unsigned char));

                unsigned count = (unsigned int)fread(data, sizeof(unsigned char), size, file);
                *bytes = count;
            }
        }
        fclose(file);
    }

    return data;
}

/*
 * LOG
 *
 */

void etracelog(int t, const char *text, ...)
{
    va_list args;
    va_start(args, text);
#if defined(SUPPORT_TRACELOG)

    char buffer[MAX_TRACELOG_MSG_LENGTH] = {0};

    switch (t)
    {
    case ELOG_TRACE:
        strcpy(buffer, "TRACE: ");
        break;
    case ELOG_DEBUG:
        strcpy(buffer, "DEBUG: ");
        break;
    case ELOG_INFO:
        strcpy(buffer, "INFO: ");
        break;
    case ELOG_WARNING:
        strcpy(buffer, "WARNING: ");
        break;
    case ELOG_ERROR:
        strcpy(buffer, "ERROR: ");
        break;
    case ELOG_FATAL:
        strcpy(buffer, "FATAL: ");
        break;
    default:
        break;
    }
    strcat(buffer, text);
    strcat(buffer, "\n");
    vprintf(buffer, args);
#endif
    va_end(args);
}

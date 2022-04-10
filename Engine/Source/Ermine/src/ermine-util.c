#include "ermine-util.h"
#include <stdarg.h>
#include <string.h>

#if defined(_WIN32)
#include <direct.h>
#else
#include <unistd.h>
#endif

#define SEPARATOR_OS '/'
#if defined(_WIN32)
#define SEPARATOR_OS '\\'
#endif

unsigned char *ermine_file_load_data(const char *filename, unsigned int *bytes)
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

const char *ermine_file_get_extension(const char *filename)
{
    printf("ermine_file_get_extension\n");

    const char *d = strrchr(filename, '.');
    return (!d || d == filename) ? NULL : d;
}

bool ermine_file_is_extension(const char *filename, const char *ext)
{
    printf("ermine_file_is_extension\n");

    char *ext_o = ermine_file_get_extension(filename);
    return strcmp(ext_o, ext) == 0 ? true : false;
}

const char *ermine_file_get_name(const char *filepath)
{
    printf("ermine_file_get_name\n");

    char *path = (filepath == NULL ? "" : filepath);
    char *base = strrchr(path, SEPARATOR_OS);
    return base ? base + 1 : path;
}

char *ermine_strncpy(char *dest, const char *src, size_t n)
{
    printf("ermine_strncpy\n");

#if defined(_WIN32)
    return strncpy_s(dest, 0, src, n);
#else
    return strncpy(dest, src, n);
#endif
}

char *ermine_strdup(const char *str)
{
    printf("ermine_strdup: %s\n", str);

#if defined(_WIN32)
    return _strdup(str);
#else
    return strdup(str);
#endif
}

char *ermine_strdup_printf(const char *format, ...)
{
    printf("ermine_strdup_printf\n");
    char buffer[256] = {0};

    va_list args;
    va_start(args, format);
    {
        vsprintf(buffer, format, args);
    }
    va_end(args);
    return ermine_strdup(buffer);
}

char *ermine_str_replace(char *string, const char *substr, const char *replacement)
{
    printf("ermine_str_replace\n");
    char *tok = NULL;
    char *newstr = NULL;
    char *oldstr = NULL;
    int oldstr_len = 0;
    int substr_len = 0;
    int replacement_len = 0;

    newstr = ermine_strdup(string);
    substr_len = strlen(substr);
    replacement_len = strlen(replacement);

    if (substr == NULL || replacement == NULL)
    {
        return newstr;
    }

    while ((tok = strstr(newstr, substr)))
    {
        oldstr = newstr;
        oldstr_len = strlen(oldstr);
        newstr = (char *)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));

        if (newstr == NULL)
        {
            free(oldstr);
            return NULL;
        }

        memcpy(newstr, oldstr, tok - oldstr);
        memcpy(newstr + (tok - oldstr), replacement, replacement_len);
        memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
        memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);

        free(oldstr);
    }

    free(string);

    return ermine_strdup(newstr);
}

char *ermine_path_normalize(const char *path)
{
    printf("ermine_path_normalize\n");

    char *new_path = NULL;
#if defined(_WIN32)
    new_path = ermine_str_replace(path, "/", "\\");
#else
    new_path = ermine_str_replace(path, "\\", "/");
#endif
    return new_path;
}

const char *ermine_path_get_current(void)
{
    printf("ermine_path_get_current\n");

    char buffer[FILENAME_MAX];

#if defined(_WIN32)
    _getcwd(buffer, FILENAME_MAX);
#else
    getcwd(buffer, FILENAME_MAX);
#endif

    return ermine_strdup(buffer);
}

const char *ermine_path_build_filename(const char *format, ...)
{
    printf("ermine_path_build_filename\n");

    char buffer[256] = {0};
    va_list args;
    va_start(args, format);
    {
        strcat(buffer, format);

        while (1)
        {
            const char *path = va_arg(args, char *);
            if (path == NULL)
                break;
            strcat(buffer, SEPARATOR_OS == '/' ? "/" : "\\");
            strcat(buffer, path);
        }
    }
    va_end(args);
    return ermine_path_normalize(ermine_strdup(buffer));
}

void ermine_tracelog(int t, const char *text, ...)
{
}

int ermine_random_number_len(int length)
{
    char *pool_number = "91234567897412589630159753852";
    char *numbers = malloc(sizeof(*numbers) * (length + 1));

    for (int i = 0; i < length; i++)
    {
        numbers[i] = pool_number[rand() % (sizeof((pool_number)) / sizeof((pool_number[0])))];
    }
    numbers[length] = '\0';
    return (int)atoi(numbers);
}

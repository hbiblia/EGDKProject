#ifndef ERMINE_STRING_H
#define ERMINE_STRING_H

#include <stdlib.h>
//#include <libgen.h>
#include <string.h>
#include <stdbool.h>

#include "ermine.h"
#include "ermine-config.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define STRDUPPF    ermine_strdup_printf
#define STRDUP      ermine_strdup
#define PATH_BUILD(...) ermine_path_build_filename(__VA_ARGS__, NULL)

ermine_public unsigned char *ermine_file_load_data(const char *filename, unsigned int *bytes);
ermine_public const char *ermine_file_get_extension(const char *filename);
ermine_public bool ermine_file_is_extension(const char *filename, const char *ext);
ermine_public const char *ermine_file_get_name(const char *filepath);

ermine_public char* ermine_strncpy(char* dest, const char* src, size_t n);
ermine_public char* ermine_strdup(const char* str);
ermine_public char *ermine_strdup_printf(const char *fmt,...);
ermine_public char *ermine_str_replace(char* string, const char* substr, const char* replacement);

ermine_public char *ermine_path_normalize(const char *path);
ermine_public const char *ermine_path_build_filename(const char *path, ...);
ermine_public const char *ermine_path_get_current(void);

ermine_public void ermine_tracelog(int t, const char *text, ...);

ermine_public int ermine_random_number_len(int length);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_STRING_H

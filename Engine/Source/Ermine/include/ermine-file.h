#ifndef ERMINE_FILE_H
#define ERMINE_FILE_H
#include <stdio.h>
#include <stdbool.h>
#include "ermine.h"

#if defined(_WIN32)
#include <direct.h>
#else
#include <unistd.h>
#endif

ermine_public unsigned char *ermine_file_load_data(const char *filename, unsigned int *bytes);
ermine_public const char *ermine_file_get_extension(const char *filename);
ermine_public bool ermine_file_is_extension(const char *filename, const char *ext);
ermine_public const char *ermine_file_get_name(const char *filepath);

#endif // ERMINE_FILE_H
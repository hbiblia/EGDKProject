#ifndef ERMINE_STRING_H
#define ERMINE_STRING_H
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ermine.h"

ermine_public int32_t ermine_strlen(const char *str);

ermine_public char *ermine_strreverse(const char *str);
ermine_public char *ermine_substring(const char *str, int start, int end);
ermine_public char *ermine_strcat(char *dest, const char *src);
ermine_public char *ermine_strncpy(char *dest, const char *src, size_t n);
ermine_public char *ermine_strdup(const char *str);
ermine_public char *ermine_strdup_printf(const char *format, ...);
ermine_public char *ermine_strreplace(const char *str, const char *find, const char *replace);

#endif // ERMINE_STRING_H
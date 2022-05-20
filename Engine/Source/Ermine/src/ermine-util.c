#include "ermine-util.h"
#include <stdarg.h>
#include <string.h>

#if defined(_WIN32)
#include <direct.h>
#else
#include <unistd.h>
#endif

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
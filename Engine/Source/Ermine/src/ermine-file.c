#include "ermine-file.h"
#include "ermine-path.h"

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
    char *path = (filepath == NULL ? "" : filepath);
    char *base = strrchr(path, SEPARATOR_OS);

    return base ? base + 1 : path;
}
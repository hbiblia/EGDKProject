#include "ermine-hash.h"
#include <string.h>

struct htdata
{
    char *key;
    void *data;
};

struct hashtable *hash_table_new(void)
{
    struct hashtable *tmp = (struct hashtable *)malloc(sizeof(struct hashtable) * 2);
    tmp->iter = array_new();
    return tmp;
}

void hash_table_insert(struct hashtable *a, const char *key, void *data)
{
    if (!hash_table_contains(a, key))
    {
        struct htdata *hash_data = (struct htdata *)malloc(sizeof(struct htdata));
        hash_data->data = data;
        hash_data->key = strdup(key);
        a->iter = array_append(a->iter, data);
    }
}

void *hash_table_lookup(struct hashtable *a, const char *key)
{
    for (int i = 0; i < array_length(a->iter); i++)
    {
        struct htdata *hash_data = array_get(a->iter, i);
        if (strcmp(key, hash_data->key) == 0)
        {
            return hash_data->data;
        }
    }
    return NULL;
}

bool hash_table_contains(struct hashtable *a, const char *key)
{
    return hash_table_lookup(a, key) == NULL ? false : true;
}

void hash_table_destroy(struct hashtable *a)
{
    for (int i = 0; i < array_length(a->iter); i++)
    {
        struct htdata *hash_data = array_get(a->iter, i);
        free(hash_data);
    }

    array_free(a->iter);
    free(a);
}

size_t hash_table_size(struct hashtable *a)
{
    return a->iter->length;
}

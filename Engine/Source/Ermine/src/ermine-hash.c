#include <string.h>
#include <stdbool.h>

#include "ermine-hash.h"
#include "ermine-util.h"
#include "array_dynamic/array_dynamic.h"

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
    printf("hash_table_insert [%s]\n", key);

    if (!hash_table_contains(a, key))
    {
        struct htdata *hash_data;

        hash_data = (struct htdata *)malloc(sizeof(struct htdata) * 1);
        hash_data->data = data;
        hash_data->key = ermine_strdup(key);
        a->iter = array_append(a->iter, hash_data);
    }
}

void *hash_table_lookup(struct hashtable *a, const char *key)
{
    printf("hash_table_lookup [%s][%zu]\n", key, array_length(a->iter));

    size_t len = array_length(a->iter);
    for (size_t i = 0; i < len; i++)
    {
        struct htdata *hash_data = (struct htdata *)array_get(a->iter, i);
        if(!hash_data)break;

        if (strcmp(key, hash_data->key) == 0)
        {
            return hash_data->data;
        }
    }
    return NULL;
}

bool hash_table_contains(struct hashtable *a, const char *key)
{
    printf("hash_table_contains [%s]\n", key);

    return hash_table_lookup(a, key) == NULL ? false : true;
}

void hash_table_destroy(struct hashtable *a)
{
    size_t len = array_length(a->iter);
    for (size_t i = 0; i < len; i++)
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

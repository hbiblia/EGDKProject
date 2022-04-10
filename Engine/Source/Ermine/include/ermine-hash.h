#ifndef ERMINE_HASH_H
#define ERMINE_HASH_H
#include <stdlib.h>
#include <stdbool.h>
#include "ermine-config.h"
#include "array_dynamic/array_dynamic.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct hashtable
{
    struct array *iter;
};

ermine_public struct hashtable *hash_table_new(void);

ermine_public void hash_table_insert(struct hashtable *a, const char *key, void *data);

ermine_public void *hash_table_lookup(struct hashtable *a, const char *key);

ermine_public bool hash_table_contains(struct hashtable *a, const char *key);

ermine_public void hash_table_destroy(struct hashtable *a);

ermine_public size_t hash_table_size(struct hashtable* a);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_HASH_H

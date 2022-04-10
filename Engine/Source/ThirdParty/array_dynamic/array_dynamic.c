#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "array_dynamic.h"

/* iniciamos un nuevo array */
struct array *array_new(void)
{
    struct array* tmp;

    tmp = (struct array*)malloc(1 * sizeof(struct array));
    tmp[0].length = 0;

    return tmp;
}

/* creamos un nuevo valor */
struct array *array_append(struct array *a, void *data)
{
    size_t len = a[0].length;
    size_t l = (len == 0 ? 1 : len);
    a = (struct array*)realloc(a, l + 1);
    a[len].data = data;
    a[0].length++;
    return a;
}

/* obtenemos un valor del array */
void *array_get(struct array *a, int index)
{
    return a[index].data;
}

/* borramos todo el array */
void array_free(struct array *a)
{
    free(a);
}

/* contamos la cantidad de datos que tienen el array */
size_t array_length(struct array *a)
{
    return a[0].length;
}

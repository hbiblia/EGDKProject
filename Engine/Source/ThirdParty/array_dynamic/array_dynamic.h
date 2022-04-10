
#ifndef ARRAY_DYNAMIC_H
#define ARRAY_DYNAMIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

struct array{
  void *data;
  size_t length;
};

/* iniciamos un nuevo array */
struct array *array_new(void);

/* agregamos un nuevo dato */
struct array* array_append(struct array* a, void* data);

/* obtenemos un valor del array */
void *array_get(struct array *a, int index);

/* liberamos todo el array */
void array_free(struct array *a);

/* obtenemos cuanto datos tenemos en el array */
size_t array_length(struct array* a);

#ifdef __cplusplus
}
#endif

#endif

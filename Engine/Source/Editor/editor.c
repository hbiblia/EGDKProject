#include "ermine.h"
#include "flower.h"

/*
 * Guardamos el level y si no tenemos uno abierto
 * lo creamos con los nuevos datos.
 *
 */

void editor_internal_level_save(void)
{
    eresource_level_save();
}

/*
 * Cargamos un level existente.
 *
 */

void editor_internal_level_open(const char *filename)
{
    eresource_level_open(filename);
}

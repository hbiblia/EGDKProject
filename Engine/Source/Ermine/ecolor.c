
#include "ermine.h"

/*
 * Color
 *
 */

bool ecolor_empty(ecolor color)
{
    bool empty = color.r == 0.0f && color.g == 0.0f && color.b == 0.0f && color.a == 0.0f;
    return empty;
}

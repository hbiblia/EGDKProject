
#include "ermine.h"

/*
 * Math
 *
 */

evect2 evect2_new(float x, float y)
{
    evect2 v = {x, y};
    return v;
}

evect3 evect3_new(float x, float y, float z)
{
    evect3 v = {x, y, z};
    return v;
}

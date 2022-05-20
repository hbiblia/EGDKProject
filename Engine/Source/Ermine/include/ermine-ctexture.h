#ifndef ERMINE_CTEXTURE_H
#define ERMINE_CTEXTURE_H
#include <stdio.h>
#include <stdbool.h>

#include "ermine-ctransform.h"
#include "ermine-ccolor.h"
#include "ermine-cmath.h"
#include "ermine-types.h"

typedef struct etexture
{
    unsigned int id;
    int width;
    int height;
} etexture;

typedef struct etexture_desc_t
{
    etexture source;
    ecolor color;
    erect clip;
    bool flipx;
    bool flipy;
    etransform transform;
} etexture_desc_t;

void ComponentTexture(ecs_world_t *world);

#endif // ERMINE_CTEXTURE_H
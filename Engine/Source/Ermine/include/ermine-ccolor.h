#ifndef ERMINE_COLOR_H
#define ERMINE_COLOR_H
#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine.h"
#include "ermine-ecs.h"

typedef struct{
    float r;
    float g;
    float b;
    float a;
}ecolor;

#define COLORD(color) ermine_color_is_empty(color) ? WHITE : color
#define ECOLOR_RGBA_T(r, g, b, a) (ecolor){(r) / 255.0f, (g) / 255.0f, (b) / 255.0f, (a) / 255.0f}

#define LIGHTGRAY  ECOLOR_RGBA_T(200, 200, 200, 255)   // Light Gray
#define GRAY       ECOLOR_RGBA_T(130, 130, 130, 255)   // Gray
#define DARKGRAY   ECOLOR_RGBA_T(80, 80, 80, 255)      // Dark Gray
#define YELLOW     ECOLOR_RGBA_T(253, 249, 0, 255)     // Yellow
#define GOLD       ECOLOR_RGBA_T(255, 203, 0, 255)     // Gold
#define ORANGE     ECOLOR_RGBA_T(255, 161, 0, 255)     // Orange
#define PINK       ECOLOR_RGBA_T(255, 109, 194, 255)   // Pink
#define RED        ECOLOR_RGBA_T(230, 41, 55, 255)     // Red
#define MAROON     ECOLOR_RGBA_T(190, 33, 55, 255)     // Maroon
#define GREEN      ECOLOR_RGBA_T(0, 228, 48, 255)      // Green
#define LIME       ECOLOR_RGBA_T(0, 158, 47, 255)      // Lime
#define DARKGREEN  ECOLOR_RGBA_T(0, 117, 44, 255)      // Dark Green
#define SKYBLUE    ECOLOR_RGBA_T(102, 191, 255, 255)   // Sky Blue
#define BLUE       ECOLOR_RGBA_T(0, 121, 241, 255)     // Blue
#define DARKBLUE   ECOLOR_RGBA_T(0, 82, 172, 255)      // Dark Blue
#define PURPLE     ECOLOR_RGBA_T(200, 122, 255, 255)   // Purple
#define VIOLET     ECOLOR_RGBA_T(135, 60, 190, 255)    // Violet
#define DARKPURPLE ECOLOR_RGBA_T(112, 31, 126, 255)    // Dark Purple
#define BEIGE      ECOLOR_RGBA_T(211, 176, 131, 255)   // Beige
#define BROWN      ECOLOR_RGBA_T(127, 106, 79, 255)    // Brown
#define DARKBROWN  ECOLOR_RGBA_T(76, 63, 47, 255)      // Dark Brown

#define WHITE      ECOLOR_RGBA_T(255, 255, 255, 255)   // White
#define BLACK      ECOLOR_RGBA_T(0, 0, 0, 255)         // Black
#define BLANK      ECOLOR_RGBA_T(0, 0, 0, 0)           // Blank (Transparent)
#define MAGENTA    ECOLOR_RGBA_T(255, 0, 255, 255)     // Magenta

bool ermine_color_is_empty(ecolor color);
ermine_public ecolor ermine_color_random(void);

ermine_private void ComponentBaseColorImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif
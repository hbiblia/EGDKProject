#ifndef ERMINE_CAMERA_H
#define ERMINE_CAMERA_H
#include <stdio.h>

#include "ermine-cmath.h"

#define CAMERA_MANAGER_SIZE 10

typedef struct
{
    int w;
    int h;
    int x;
    int y;
} eviewport;

typedef struct
{
    evec2 offset;   // Camera offset (displacement from target)
    evec2 target;   // Camera target (rotation and zoom origin)
    float rotation; // Camera rotation in degrees
    float zoom;     // Camera zoom (scaling), should be 1.0f by default
    eviewport viewport;
} ecamera;

enum
{
    CAMERA1 = 1,
    CAMERA2,
    CAMERA3,
    CAMERA4,
    CAMERA5,
    CAMERA6,
    CAMERA7,
    CAMERA8,
    CAMERA9
};

ermine_public void ermine_camera_set_active(int i);
ermine_public ecamera ermine_camera_get_active(void);
ermine_public void ermine_camera_set(ecamera camera, int index);

ermine_public void ermine_camera_manager_end(void);
ermine_public void ermine_camera_manager_begin(int camera_id);

#endif // ERMINE_CAMERA_H
#ifndef ERMINE_C_BACKGROUND_TILING_H
#define ERMINE_C_BACKGROUND_TILING_H
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "ermine.h"
#include "ermine-ecs.h"
#include "ermine-ccolor.h"
#include "ermine-crenderer.h"

typedef struct {
    evec2 tilingPosition;
    evec2 tilingScale;
    ecs_f32_t tilingAngle;
    // renderer component required
    erenderer renderer;
}ecBackgroundTiling;

ermine_private void ComponentBackgroundTilingImport(ecs_world_t *world);

#ifdef __cplusplus
}
#endif

#endif // ERMINE_C_BACKGROUND_TILING_H

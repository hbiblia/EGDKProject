#ifndef COMPONENTS_H
#define COMPONENTS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <ermine.h>
#include "ermine-flower.h"

#include "Components/component.base.h"
#include "Components/InfoComponent.h"
#include "Components/TransformComponent.h"
#include "Components/DamageComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/AnimateSpriteComponent.h"

void components_init(void)
{
    ecs_world_t *world = flower_get_world();

    ComponentBaseImport(world);
    ComponentInfoImport(world);
    ComponentTransformImport(world);

    DamageComponentInit(world);
    AnimateSpriteComponentImport(world);
    SpriteRendererComponentImport(world);
}

#ifdef __cplusplus
}
#endif

#endif // COMPONENTS_H

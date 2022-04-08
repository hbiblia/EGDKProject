#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <ermine.h>
#include "ermine-flower.h"

#include "component.base.h"
#include "InfoComponent.h"
#include "TransformComponent.h"
#include "DamageComponent.h"
#include "SpriteRendererComponent.h"
#include "AnimateSpriteComponent.h"

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

#endif // COMPONENTS_H

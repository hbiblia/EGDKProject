#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <ermine.h>
#include "flower.h"

#include "InfoComponent.h"
#include "TransformComponent.h"
#include "DamageComponent.h"
// #include "SpriteRendererComponent.h"
// #include "AnimateSpriteComponent.h"

void components_init(void)
{
    ecs_world_t *world = flower_get_world();

    DamageComponentInit(world);

    ComponentBaseImport(world);
    ComponentInfoImport(world);
    ComponentTransformImport(world);
    ComponentSpriteRendererImport(world);
    ComponentSpriteRendererImport(world);
    ComponentAnimateSpriteImport(world);
}

#endif // COMPONENTS_H

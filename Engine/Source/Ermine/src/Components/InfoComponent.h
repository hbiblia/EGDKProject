#pragma once

#ifndef INFOCOMPONENT_H
#define INFOCOMPONENT_H

#include <flecs/flecs.h>
#include <ermine.h>
#include "ermine-flower.h"

#undef ECS_META_IMPL
#ifndef InfoComponent_EXPORTS
#define ECS_META_IMPL EXTERN // Ensure meta symbols are only defined once
#endif

ECS_STRUCT(InfoComponent, {
    char *name;
    ECS_PRIVATE
    int8_t id;
});

ermine_public void ComponentInfoImport(ecs_world_t *world);

#endif // INFOCOMPONENT_H_

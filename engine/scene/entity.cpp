#include "entity.h"

#include "scene.h"

Entity::Entity(entt::entity handle, Scene* scene)
    :entity_handle(handle)
    ,scene(scene)
{
}
